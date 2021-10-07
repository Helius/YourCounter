#include "transactionjsonmapper.h"

namespace TransactionJsonMapper {

    Transaction fromJson(const QString &id, const QJsonObject &obj) {
        float amount = obj.value("amount").toDouble(0);
        QDateTime when = QDateTime::fromSecsSinceEpoch(obj.value("when").toInteger());
        QString who = obj.value("who").toString();
        QString categoryId = obj.value("category").toString();
        QString comment = obj.value("comment").toString();
        return Transaction(id, amount, when, categoryId, who, comment);
    }

    Transactions parseTransaction(const QJsonObject &transactions) {
        Transactions result;
        for (auto it = transactions.constBegin(); it != transactions.constEnd(); ++it) {
            result.push_back(fromJson(it.key(), it.value().toObject()));
        }
        return result;
    }

    Categories parseCategories(const QJsonObject &categories) {

        Categories result;
        for (auto it = categories.constBegin(); it != categories.constEnd(); ++it) {
            result.push_back(Category(it.key(), it.value().toObject().value("name").toString()));
        }
        return result;
    }

    QJsonObject toJson(const CategoryRequest &request) {
        return {{"name", request.name}};
    }

    QJsonObject toJson(const TransactionRequest &request) {
        return {
                {"categoryId", request.categoryId},
                {"amount", request.amount},
                {"when", request.when.toSecsSinceEpoch()},
                {"who", request.who},
                {"comment", request.comment}
        };
    }

} // namespace
