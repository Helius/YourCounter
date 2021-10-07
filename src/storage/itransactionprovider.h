#pragma once

#include <QObject>
#include <entities/transaction.h>

class ITransactionProvider : public QObject
{
        Q_OBJECT

public:
        virtual void loadData() = 0;
signals:
        void transactionReady(Transactions transaction);

public:
        virtual ~ITransactionProvider() = default;
        using QObject::QObject;
};

using ITransactionProviderUnq = std::unique_ptr<ITransactionProvider>;
