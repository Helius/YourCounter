#ifndef TRANSACTIONREPO_H
#define TRANSACTIONREPO_H

#include <QObject>
#include <domain/repos/itransactionrepo.h>
#include <app/repos/itransactionprovider.h>

class IDateColumnAdapter;

class TransactionRepo : public ITransactionRepo
{
    Q_OBJECT
public:
    explicit TransactionRepo(std::shared_ptr<IDateColumnAdapter> dateAdapter, ITransactionProviderUnq provider);

    // ITransactionRepo interface
public:
    float calcAmount(int categoryInd, int dayNumber) override;
    const Categories & getCategories() override;
    bool hasColumnAmount(int column) override;
    float columnAmountOverAll(int column) override;
    float max() override { return m_max; }
    float min() override { return m_min; }
    void addTransaction(Transaction t) override;
    const Transactions &getTransactions() override;

private:
    void updateCategories();
private:
    std::vector<Transaction> m_transactions;
    std::vector<QString> m_categories;
    std::shared_ptr<IDateColumnAdapter> m_dateAdapter;
    ITransactionProviderUnq m_provider;
    float m_min = 0.0;
    float m_max = 0.0;

};

#endif // TRANSACTIONREPO_H
