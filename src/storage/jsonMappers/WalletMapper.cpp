#include "WalletMapper.h"

namespace {

QLatin1String nameKey("name");
QLatin1String srcCategoryIdKey("srcCat");
QLatin1String fixTimeKey("fixTime");
QLatin1String fixedAmountKey("fixedAmount");

QDateTime valueToTime(const QJsonValue& val)
{
    return QDateTime::fromMSecsSinceEpoch(val.toInteger());
}

qint64 timeToValue(const QDateTime& time)
{
    return time.toMSecsSinceEpoch();
}

} // namespace

Wallet WalletMapper::fromJson(const QString& id, const QJsonObject& json)
{
    QString name = json[nameKey].toString();
    QString srcId = json[srcCategoryIdKey].toString();
    QDateTime fixTime;
    if (json.contains(fixTimeKey)) {
        fixTime = valueToTime(json.value(fixTimeKey));
    }
    int64_t fixedAmount = json.value(fixedAmountKey).toInt(0);
    return Wallet::createFromValue(id, name, CategoryId(srcId), fixTime, fixedAmount);
}

QJsonObject WalletMapper::toJson(const Wallet& t)
{
    QJsonObject result = {
        { nameKey, t.name },
        { srcCategoryIdKey, t.srcId.toString() },
    };

    if (t.fixTime.isValid()) {
        result.insert(fixTimeKey, timeToValue(t.fixTime));
        result.insert(fixedAmountKey, static_cast<int>(t.fixedAmount));
    }

    return result;
}

void WalletMapper::patch(Wallet& t, const QJsonObject& json)
{
    t.name = json.contains(nameKey) ? json[nameKey].toString() : t.name;
    t.srcId = json.contains(srcCategoryIdKey) ? CategoryId(json[nameKey].toString()) : t.srcId;
    t.fixedAmount = json.contains(fixedAmountKey) ? json[fixedAmountKey].toInt(0) : t.fixedAmount;
    t.fixTime = json.contains(fixTimeKey) ? valueToTime(json[fixTimeKey]) : t.fixTime;
}

QJsonObject WalletMapper::diff(const Wallet& from, const Wallet& to)
{
    QJsonObject result;

    if (from.name != to.name) {
        result.insert(nameKey, to.name);
    }

    if (from.srcId != to.srcId) {
        result.insert(srcCategoryIdKey, to.srcId.toString());
    }

    if (from.fixTime != to.fixTime) {
        result.insert(fixTimeKey, timeToValue(to.fixTime));
    }

    if (from.fixedAmount != to.fixedAmount) {
        result.insert(fixedAmountKey, static_cast<int>(to.fixedAmount));
    }

    return result;
}
