#include "TransactionMapper.h"

namespace {
QLatin1String amountKey("amount");
QLatin1String categoryIdKey("categoryId");
QLatin1String walletIdKey("walletId");
QLatin1String whenKey("when");
QLatin1String whoKey("who");
QLatin1String commentKey("comment");
}

Transaction TransactionMapper::fromJson(const QString& id, const QJsonObject& json)
{
    int64_t amount = json.value(amountKey).toInt(0);
    QDateTime when = QDateTime::fromMSecsSinceEpoch(json.value(whenKey).toInteger());
    QString who = json.value(whoKey).toString();
    QString categoryId = json.value(categoryIdKey).toString();
    WalletId walletId = WalletId(json.value(walletIdKey).toString(QString()));
    QString comment = json.value(commentKey).toString();

    return Transaction::createFromValue(id, amount, when, categoryId, walletId, who, comment);
}

QJsonObject TransactionMapper::toJson(const Transaction& t)
{
    return {
        { categoryIdKey, t.categoryId },
        { amountKey, static_cast<int>(t.amount) },
        { whenKey, t.when.toMSecsSinceEpoch() },
        { walletIdKey, t.walletId.toString() },
        { whoKey, t.who },
        { commentKey, t.comment }
    };
}

void TransactionMapper::patch(Transaction& t, const QJsonObject& json)
{
    t.categoryId = json.contains(categoryIdKey) ? json.value(categoryIdKey).toString() : t.categoryId;
    t.amount = json.contains(amountKey) ? json.value(amountKey).toInt() : t.amount;
    t.when = json.contains(whenKey) ? QDateTime::fromMSecsSinceEpoch(json.value(whenKey).toInteger()) : t.when;
    t.who = json.contains(whoKey) ? json.value(whoKey).toString() : t.who;
    t.comment = json.contains(commentKey) ? json.value(commentKey).toString() : t.comment;
    t.walletId = json.contains(walletIdKey)
        ? WalletId(json.value(walletIdKey).toString(QString()))
        : t.walletId;
}

QJsonObject TransactionMapper::diff(const Transaction& from, const Transaction& to)
{
    QJsonObject result;
    if (to.amount != from.amount) {
        result.insert(amountKey, static_cast<int>(to.amount));
    }
    if (to.categoryId != from.categoryId) {
        result.insert(categoryIdKey, to.categoryId);
    }
    if (to.when != from.when) {
        result.insert(whenKey, to.when.toMSecsSinceEpoch());
    }
    if (to.who != from.who) {
        result.insert(whoKey, to.who);
    }
    if (to.comment != from.comment) {
        result.insert(commentKey, to.comment);
    }
    if (to.walletId != from.walletId) {
        result.insert(walletIdKey, to.walletId.toString());
    }
    return result;
}
