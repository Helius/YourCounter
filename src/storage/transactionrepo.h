#pragma once

#include <QObject>
#include <repos/itransactionrepo.h>
#include "firebaseRtDbAPI.h"
#include <QFuture>


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
