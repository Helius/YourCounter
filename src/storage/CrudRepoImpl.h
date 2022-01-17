#pragma once

#include <QFuture>
#include <QJsonDocument>

#include <repos/ICRUDRepo.h>

#include "firebaseRtDbAPI.h"
#include "jsonMappers/IJsonMapper.h"

template <typename Entity>
class CrudRepository : public ICRUDRepo<Entity> {
public:
    using IJsonMapperPtr = std::shared_ptr<IJsonMapper<Entity>>;
    CrudRepository() = delete;
    ~CrudRepository() = default;

    CrudRepository(const QString& entryPoint,
        IFirebaseRtDbAPIPtr api,
        IJsonMapperPtr mapper)
        : m_entryPoint(entryPoint)
        , m_api(api)
        , m_mapper(mapper)
    {
        Q_ASSERT(m_api);
        Q_ASSERT(m_mapper);
    }

    void create(const Entity& e) override
    {
        m_api->addObject(m_entryPoint, m_mapper->toJson(e))
            .then(this, [this, e](const QJsonObject& response) {
                Entity entity = e;
                entity.id = getKeyFromResponse(response);
                if (!entity.id.isEmpty()) {
                    m_data.push_back(entity);
                    emit IRepoObserver::dataChanged(IRepoObserver::Inserted, m_data.size() - 1, 1);
                } else {
                    emit IRepoObserver::onError(QString("Smth wrong in ") + Q_FUNC_INFO);
                }
            });
    }

    void remove(const Entity& e) override
    {
        m_api->deleteObject(m_entryPoint, e.id)
            .then(this, [this, id = e.id](const QJsonObject& response) {
                if (response.isEmpty()) {
                    auto it = std::find_if(m_data.begin(), m_data.end(),
                        [id](const auto& object) {
                            return object.id == id;
                        });
                    if (it != m_data.end()) {
                        auto ind = std::distance(m_data.begin(), it);
                        m_data.erase(it);
                        emit IRepoObserver::dataChanged(IRepoObserver::Removed, ind, 1);
                    } else {
                        emit IRepoObserver::onError(
                            QString("Couldn't find object with id while DELETE it ") + Q_FUNC_INFO);
                    }
                } else {
                    emit IRepoObserver::onError(
                        QString("Json should be empty on DELETE rest method, got: ") + QJsonDocument(response).toJson() + Q_FUNC_INFO);
                }
            });
    }

    void update(const Entity& newE) override
    {
        const auto it = std::find_if(m_data.cbegin(), m_data.cend(), [id = newE.id](const auto& e) { return e.id == id; });
        if (it != m_data.cend()) {
            const auto diff = m_mapper->diff(*it, newE);
            m_api->updateObject(m_entryPoint, newE.id, diff)
                .then([this, diff, ind = std::distance(m_data.cbegin(), it)](const QJsonObject& response) {
                    if (diff != response) {
                        emit IRepoObserver::onError(
                            QString("Looks like patch is not same. Sended ")
                            + QJsonDocument(diff).toJson() + "received:"
                            + QJsonDocument(response).toJson() + Q_FUNC_INFO);
                    }
                    m_mapper->patch(m_data[ind], response);
                    emit IRepoObserver::dataChanged(IRepoObserver::Changed, ind, 1);
                });
        } else {
            emit IRepoObserver::onError(
                QString("Couldn't find object with id while UPDATE it ") + Q_FUNC_INFO);
        }
    }

    void fetchAll() override
    {
        m_fetched = false;
        const auto size = m_data.size();
        if (size != 0) {
            m_data.clear();
            emit IRepoObserver::dataChanged(IRepoObserver::Removed, 0, size);
        }

        m_api->getObject(m_entryPoint)
            .then(this, [this](const QJsonObject& json) {
                for (const auto& key : json.keys()) {
                    const auto& val = json.value(key).toObject();
                    if (auto e = m_mapper->fromJson(key, val)) {
                        m_data.push_back(std::move(e));
                    } else {
                        qWarning() << "Can't parse object from json: " << QJsonDocument(val).toJson() << Q_FUNC_INFO;
                    }
                }
                m_fetched = true;
                emit IRepoObserver::dataChanged(IRepoObserver::Inserted, 0, m_data.size());
            });
    }

    bool fetched() override
    {
        return m_fetched;
    };

    const std::vector<Entity>& data() override { return m_data; }

private:
    QString getKeyFromResponse(const QJsonObject& object)
    {
        const auto keys = object.keys();
        Q_ASSERT(keys.size() == 1);
        if (keys.size() == 1) {
            return object.value(keys.front()).toString();
        }
        return QString();
    }

private:
    std::vector<Entity> m_data;
    QString m_entryPoint;
    IFirebaseRtDbAPIPtr m_api;
    IJsonMapperPtr m_mapper;
    bool m_fetched = false;
};
