#ifndef TRANSACTIONREPO_H
#define TRANSACTIONREPO_H

#include <QObject>
#include "itransactionrepo.h"

class IDateColumnAdapter;

class TransactionRepo : public ITransactionRepo
{
    Q_OBJECT
public:
    explicit TransactionRepo(IDateColumnAdapter * dateAdapter, QObject *parent = nullptr);

    // ITransactionRepo interface
public:
    float calcAmount(int categoryInd, int dayNumber) override;
    const std::vector<QString> & getCategories() override;
    bool hasColumnAmount(int column) override;
    float columnAmountOverAll(int column) override;

private:
    std::vector<Transaction> m_transactions;
    std::vector<QString> m_categories;
    IDateColumnAdapter * m_dateAdapter;
};

#endif // TRANSACTIONREPO_H
