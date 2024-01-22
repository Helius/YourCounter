#pragma once
#include <QObject>
#include <QString>

class IRepoObserver : public QObject {

    Q_OBJECT

public:
    enum UpdateMode {
        Changed = 0,
        Inserted,
        Removed,
    };
    Q_ENUM(UpdateMode);
signals:
    void dataChanged(UpdateMode mode, size_t startIndex, size_t size);
    void onError(const QString& error);
};

template <typename Entity>
class ICRUDRepo : public IRepoObserver {
public:
    virtual void fetchAll() = 0;
    virtual void create(const Entity& t) = 0;
    virtual void remove(const Entity& t) = 0;
    virtual void update(const Entity& t) = 0;
    virtual bool fetched() = 0;
    virtual const std::vector<Entity>& data() = 0;
    virtual std::optional<Entity> find(const QString& id) = 0;
    virtual ~ICRUDRepo() = default;
};
