#ifndef ITRANSACTIONREPO_H
#define ITRANSACTIONREPO_H

#include <QObject>
#include <entities/transaction.h>

using Categories = std::vector<QString>;

class ITransactionRepo : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;
    ~ITransactionRepo() = default;
    virtual bool hasDailyAmount(int dayNumber) = 0;
    virtual float dailyAmountOverAll(int dayNumber) = 0;
    virtual float calcAmount(int categoryInd, int dayMumber) = 0;
    virtual const std::vector<QString> & getCategories() = 0;
signals:
    void dataChanged();

};

#endif // ITRANSACTIONREPO_H
