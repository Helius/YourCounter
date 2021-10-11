#include <entities/Group.h>
#include <entities/GroupRequest.h>
#include "transactionjsonmapper.h"

#include <QJsonDocument>

namespace {
    QLatin1String idKey("id");
    QLatin1String amountKey("amount");
    QLatin1String categoryIdKey("categoryId");
    QLatin1String whenKey("when");
    QLatin1String whoKey("who");
    QLatin1String commentKey("comment");
}

namespace TransactionJsonMapper {

    Transaction transactionFromJson(const QString & id, const QJsonObject &obj) {
        float amount = obj.value(amountKey).toDouble(0);
        QDateTime when = QDateTime::fromSecsSinceEpoch(obj.value(whenKey).toInteger());
        QString who = obj.value(whoKey).toString();
        QString categoryId = obj.value(categoryIdKey).toString();
        QString comment = obj.value(commentKey).toString();
        return Transaction(id, amount, when, categoryId, who, comment);
    }

    Transactions parseTransactions(const QJsonObject &transactions) {
        Transactions result;
        for (auto it = transactions.constBegin(); it != transactions.constEnd(); ++it) {
            result.push_back(transactionFromJson(it.key(), it.value().toObject()));
        }
        return result;
    }

    QJsonObject toJson(const TransactionRequest &request) {
        return {
                {categoryIdKey, request.categoryId},
                {amountKey, request.amount},
                {whenKey, request.when.toSecsSinceEpoch()},
                {whoKey, request.who},
                {commentKey, request.comment}
        };
    }

    QJsonObject diff(const Transaction & newT, const Transaction & oldT)
    {
        QJsonObject result;
        if(newT.amount != oldT.amount) {
            result.insert(amountKey, newT.amount);
        }
        if(newT.categoryId != oldT.categoryId) {
            result.insert(categoryIdKey, newT.categoryId);
        }
        if(newT.when != oldT.when) {
            result.insert(whenKey, newT.when.toSecsSinceEpoch());
        }
        if(newT.who != oldT.who) {
            result.insert(whoKey, newT.who);
        }
        if(newT.comment != oldT.comment) {
            result.insert(commentKey, newT.comment);
        }
        return result;
    }

} // namespace
