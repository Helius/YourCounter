#pragma once

#include <QObject>
#include <QJsonObject>
#include <entities/transaction.h>
#include <entities/Category.h>
#include <entities/CategoryRequest.h>
#include <entities/TransactionRequest.h>
#include <entities/Group.h>
#include <entities/GroupRequest.h>

class ITransactionRepo : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;
    ~ITransactionRepo() = default;
    virtual const Transactions & getTransactions() = 0;
    virtual const Transactions & getPredictions() = 0;
    virtual const Categories & getCategories() = 0;
    virtual const Groups & getGroups() = 0;
    virtual void addTransaction(const TransactionRequest & tr) = 0;
    virtual void addPrediction(const TransactionRequest & tr) = 0;
    virtual void addCategory(const CategoryRequest & cr) = 0;
    virtual void addGroup(const GroupRequest & gr) = 0;
    virtual void setTransactionCategory(const Transaction & t, const Category & c) = 0;
    virtual void setCategoryGroup(const Category & c, const Group & g) = 0;

signals:
    void transactionsChanged();
    void categoriesChanged();
    void groupsChanged();
    void predictionsChanged();
};

using ITransactionRepoPtr = std::shared_ptr<ITransactionRepo>;
