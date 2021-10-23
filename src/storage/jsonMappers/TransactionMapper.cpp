#include <entities/Group.h>
#include <entities/GroupRequest.h>
#include "TransactionMapper.h"

#include <QJsonDocument>

namespace {
    QLatin1String amountKey("amount");
    QLatin1String categoryIdKey("categoryId");
    QLatin1String whenKey("when");
    QLatin1String whoKey("who");
    QLatin1String commentKey("comment");
}

Transaction TransactionMapper::fromJson(const QString &id, const QJsonObject &json) {
    float amount = json.value(amountKey).toDouble(0);
    QDateTime when = QDateTime::fromMSecsSinceEpoch(json.value(whenKey).toInteger());
    QString who = json.value(whoKey).toString();
    QString categoryId = json.value(categoryIdKey).toString();
    QString comment = json.value(commentKey).toString();
    return Transaction(id, amount, when, categoryId, who, comment);
}

QJsonObject TransactionMapper::toJson(const Transaction &t) {
    return {
            {categoryIdKey, t.categoryId},
            {amountKey, t.amount},
            {whenKey, t.when.toMSecsSinceEpoch()},
            {whoKey, t.who},
            {commentKey, t.comment}
    };
}

void TransactionMapper::patch(Transaction &t, const QJsonObject &json) {
    t.categoryId = json.contains(categoryIdKey) ? json.value(categoryIdKey).toString() : t.categoryId;
    t.amount = json.contains(amountKey) ? json.value(amountKey).toDouble() : t.amount;
    t.when = json.contains(whenKey) ? QDateTime::fromMSecsSinceEpoch(json.value(whenKey).toInt()) : t.when;
    t.who = json.contains(whoKey) ? json.value(whoKey).toString() : t.who;
    t.comment = json.contains(commentKey) ? json.value(commentKey).toString() : t.comment;
}

QJsonObject TransactionMapper::diff(const Transaction &from, const Transaction &to) {
    QJsonObject result;
    if(to.amount != from.amount) {
        result.insert(amountKey, to.amount);
    }
    if(to.categoryId != from.categoryId) {
        result.insert(categoryIdKey, to.categoryId);
    }
    if(to.when != from.when) {
        result.insert(whenKey, to.when.toMSecsSinceEpoch());
    }
    if(to.who != from.who) {
        result.insert(whoKey, to.who);
    }
    if(to.comment != from.comment) {
        result.insert(commentKey, to.comment);
    }
    return result;
}
