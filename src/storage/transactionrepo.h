#pragma once

#include <QObject>
#include <repos/itransactionrepo.h>
#include "firebaseRtDbAPI.h"
#include <QFuture>

class IDateColumnAdapter;

class TransactionRepo : public ITransactionRepo
{
    Q_OBJECT
public:
    explicit TransactionRepo(FirebaseRtDbAPIUnq api);

    const Transactions & getTransactions() override;
    const Transactions & getPredictions() override;
    const Categories & getCategories() override;
    const Groups & getGroups() override;
    void addTransaction(const TransactionRequest & tr) override;
    void addPrediction(const TransactionRequest &tr) override;
    void addCategory(const CategoryRequest & cr) override;
    void addGroup(const GroupRequest & gr) override;
    void setTransactionCategory(const Transaction & t, const Category & c) override;
    void setCategoryGroup(const Category & c, const Group & g) override;
private:
    void init();

private:
    FirebaseRtDbAPIUnq m_api;
    Transactions m_transactions;
    Categories m_categories;
    Transactions m_predictions;
    Groups m_groups;
    QFuture<void> m_loadTransactions;
    QFuture<void> m_loadCategories;
    QFuture<void> m_loadPredictions;
    QFuture<void> m_loadGroups;
};
