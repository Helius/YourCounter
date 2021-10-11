#pragma once

#include <QJsonObject>
#include <entities/transaction.h>
#include <entities/TransactionRequest.h>

namespace TransactionJsonMapper
{
    Transactions parseTransactions(const QJsonObject & transactions);

    Transaction transactionFromJson(const QString & id, const QJsonObject & object);

    QJsonObject toJson(const TransactionRequest & request);

    QJsonObject diff(const Transaction & newT, const Transaction & oldT);
}

