#pragma once

#include <QJsonObject>
#include <entities/transaction.h>
#include <entities/Category.h>
#include <entities/CategoryRequest.h>
#include <entities/TransactionRequest.h>

namespace TransactionJsonMapper
{
    Transactions parseTransactions(const QJsonObject & transactions);
    Categories parseCategories(const QJsonObject & transactions);
    Groups parseGroups(const QJsonObject & groups);
    Transaction fromJson(const QString & id, const QJsonObject & object);
    QJsonObject toJson(const CategoryRequest & request);
    QJsonObject toJson(const TransactionRequest & request);
    QJsonObject toJson(const GroupRequest &request);
}

