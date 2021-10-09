#include <entities/Group.h>
#include <entities/GroupRequest.h>
#include "transactionjsonmapper.h"

namespace {
    QLatin1String idKey("id");
    QLatin1String amountKey("amount");
    QLatin1String categoryIdKey("categoryId");
    QLatin1String whenKey("when");
    QLatin1String whoKey("who");
    QLatin1String commentKey("comment");
}

namespace TransactionJsonMapper {

    Transaction fromJson(const QString &id, const QJsonObject &obj) {
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
            result.push_back(fromJson(it.key(), it.value().toObject()));
        }
        return result;
    }

    Groups parseGroups(const QJsonObject & groups) {
        Groups result;
        for(auto it = groups.constBegin(); it != groups.constEnd(); ++it) {
            result.push_back(Group(it.key(), it.value().toObject().value("name").toString()));
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

    QJsonObject toJson(const GroupRequest &request) {
        return {{"name", request.name}};
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
