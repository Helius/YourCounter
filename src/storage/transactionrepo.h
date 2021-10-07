#pragma once

#include <QObject>
#include <repos/itransactionrepo.h>
#include "firebaseRtDbAPI.h"

class IDateColumnAdapter;

class TransactionRepo : public ITransactionRepo
{
    Q_OBJECT
public:
    explicit TransactionRepo(FirebaseRtDbAPIUnq api);

    const Transactions & getTransactions() override;
    const Transactions & getPredictions() override;
    const Categories & getCategories() override;
    void addTransaction(const TransactionRequest & t) override;
    void addCategory(const CategoryRequest & categoryRequest) override;

private:
    void init();

private:
    FirebaseRtDbAPIUnq m_api;
    Transactions m_transactions;
    Categories m_categories;
    Transactions m_predictions;

    void emitIfReady();
};
