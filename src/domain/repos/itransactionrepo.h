#pragma once

#include <QObject>
#include <QJsonObject>
#include <entities/transaction.h>
#include <entities/Category.h>
#include <entities/CategoryRequest.h>
#include <entities/TransactionRequest.h>


class ITransactionRepo : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;
    ~ITransactionRepo() = default;
    virtual const Transactions & getTransactions() = 0;
    virtual const Transactions & getPredictions() = 0;
    virtual const Categories & getCategories() = 0;
    virtual void addTransaction(const TransactionRequest & t) = 0;
    virtual void addCategory(const CategoryRequest & categoryRequest) = 0;

signals:
    void dataChanged();
};

using ITransactionRepoPtr = std::shared_ptr<ITransactionRepo>;
