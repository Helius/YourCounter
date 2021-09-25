#ifndef TRANSACTIONJSONMAPPER_H
#define TRANSACTIONJSONMAPPER_H

#include <QJsonObject>
#include <domain/entities/transaction.h>

namespace TransactionJsonMapper
{

Transaction fromJson(const QJsonObject & object);
QJsonObject toJson(const Transaction & transaction);

}

#endif // TRANSACTIONJSONMAPPER_H
