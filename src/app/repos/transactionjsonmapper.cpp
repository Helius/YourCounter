#include "transactionjsonmapper.h"

namespace TransactionJsonMapper {


Transaction fromJson(const QJsonObject & obj)
{
    float amount = obj.value("amount").toDouble(0);
    QString category = obj.value("category").toString();
    if(category.isEmpty())
    {
        category = "Без категории";
    }
    QString comment = obj.value("comment").toString();
    QDateTime when = QDateTime::fromString(obj.value("when").toString(), Qt::DateFormat::ISODate);
    return Transaction(category, amount, when, comment);
}

QJsonObject toJson(const Transaction & transaction)
{
    return {
        {"amount", transaction.amount},
        {"category", transaction.category},
        {"comment", transaction.coment},
        {"when", transaction.when.toString(Qt::DateFormat::ISODate)}
    };
}

}
