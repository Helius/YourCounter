#ifndef TRANSACTIONREPO_H
#define TRANSACTIONREPO_H

#include <QObject>
#include "itransactionrepo.h"

class TransactionRepo : public ITransactionRepo
{
    Q_OBJECT
public:
    explicit TransactionRepo(QObject *parent = nullptr);

    // ITransactionRepo interface
public:
    float calcAmount(int categoryInd, int dayNumber);
    const std::vector<QString> & getCategories();
    bool hasDailyAmount(int dayNumber);
    float dailyAmountOverAll(int dayNumber);

private:
    std::vector<Transaction> m_transactions;
    std::vector<QString> m_categories;
};

#endif // TRANSACTIONREPO_H
