#ifndef TRANSACTIONPROVIDERFROMFILE_H
#define TRANSACTIONPROVIDERFROMFILE_H

#include "itransactionprovider.h"
#include <QObject>

class TransactionProviderFromFile : public ITransactionProvider
{
    Q_OBJECT
public:
    TransactionProviderFromFile(const QString & filePath, QObject * parent = nullptr);

    // ITransactionProvider interface
public:
    void loadTransactions() override;

private:
    QString m_filePath;
    Transactions m_transactions;
};

#endif // TRANSACTIONPROVIDERFROMFILE_H
