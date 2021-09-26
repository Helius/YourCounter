#ifndef ITRANSACTIONREPO_H
#define ITRANSACTIONREPO_H

#include <QObject>
#include <domain/entities/transaction.h>

using Categories = std::vector<QString>;

class ITransactionRepo : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;
    ~ITransactionRepo() = default;
    virtual const Transactions & transactions() = 0;
    virtual bool hasColumnAmount(int column) = 0;
    virtual float columnAmountOverAll(int column) = 0;
    virtual float calcAmount(int categoryInd, int dayMumber) = 0;
    virtual const std::vector<QString> & getCategories() = 0;
    virtual void addTransaction(Transaction t) = 0;
    virtual float max() = 0;
    virtual float min() = 0;
signals:
    void dataChanged();
};

using ITransactionRepoPtr = std::shared_ptr<ITransactionRepo>;

#endif // ITRANSACTIONREPO_H
