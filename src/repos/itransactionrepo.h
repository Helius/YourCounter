#ifndef ITRANSACTIONREPO_H
#define ITRANSACTIONREPO_H

#include <QObject>
#include <src/entities/transaction.h>

using Categories = std::vector<QString>;

class ITransactionRepo : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;
    ~ITransactionRepo() = default;
    virtual bool hasColumnAmount(int column) = 0;
    virtual float columnAmountOverAll(int column) = 0;
    virtual float calcAmount(int categoryInd, int dayMumber) = 0;
    virtual const std::vector<QString> & getCategories() = 0;
signals:
    void dataChanged();

};

#endif // ITRANSACTIONREPO_H
