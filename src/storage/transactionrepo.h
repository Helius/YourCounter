#pragma once

#include <QObject>
#include <repos/itransactionrepo.h>
#include "firebaseRtDbAPI.h"
#include <QFuture>
#include "jsonMappers/IJsonMapper.h"


class IRepoObserver : public QObject {
    Q_OBJECT
signals:
    void dataChanged(int index);
};

template <typename Entity>
class ICRUDMethods : public IRepoObserver
{
public:
    virtual void create(const Entity & t) = 0;
    virtual void remove(const Entity & t) = 0;
    virtual void update(const Entity & t) = 0;
    virtual const std::vector<Entity> & data() = 0;
};

template<typename Entity>
class CrudRepository : public ICRUDMethods<Entity>
{
public:
    CrudRepository() = delete;
    CrudRepository(const QString & entryPoint, std::unique_ptr<IJsonMapper<Entity>> mapper)
            : m_entryPoint(entryPoint)
            , m_mapper(std::move(mapper))
    {}

    void create(const Entity & e) override {
        m_mapper->toJson(e);
        m_data.push_back(e);
        emit IRepoObserver::dataChanged(m_data.size()-1);
    }

    void remove(const Entity & ) override {};
    void update(const Entity & ) override {};

    const std::vector<Entity> & data() override { return m_data; }

    std::vector<Entity> m_data;
    QString m_entryPoint;
    std::unique_ptr<IJsonMapper<Entity>> m_mapper;
};
/*
class TransactionRepo
    : public ITransactionRepo
    , public QEnableSharedFromThis<ITransactionRepo>
{
Q_OBJECT
public:
    TransactionRepo() = delete;
    ~TransactionRepo() override;

    void init() override;
    const Transactions & getTransactions() override;
    const Transactions & getPredictions() override;
    const Categories & getCategories() override;
    const Groups & getGroups() override;

    void addTransaction(const TransactionRequest & ) override;
    void addPrediction(const TransactionRequest &) override;
    void addCategory(const CategoryRequest & ) override;
    void addGroup(const GroupRequest & ) override;

    void updateTransaction(const Transaction & ) override;
    void updatePrediction(const Transaction & ) override;
    void updateCategory(const Category & ) override;
    void updateGroup(const Group & ) override;

    static QSharedPointer<ITransactionRepo> getInstance(IFirebaseRtDbAPIUnq api);

private:
    explicit TransactionRepo(IFirebaseRtDbAPIUnq api);

private:
    IFirebaseRtDbAPIUnq m_api;
    Transactions m_transactions;
    Categories m_categories;
    Transactions m_predictions;
    Groups m_groups;
    QFuture<void> m_loadTransactions;
    QFuture<void> m_loadCategories;
    QFuture<void> m_loadPredictions;
    QFuture<void> m_loadGroups;

    QSharedPointer<ITransactionRepo> gePtr();
};
*/