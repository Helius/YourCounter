#include "WalletMapper.h"

namespace {

QLatin1String nameKey("name");
QLatin1String initTimeKey("initTime");
QLatin1String initAmountKey("initAmount");
QLatin1String isDefaultKey("default");

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
    QDateTime initTime;
    if (json.contains(initTimeKey)) {
        initTime = valueToTime(json.value(initTimeKey));
    }
    int64_t initAmount = json.value(initAmountKey).toInt(0);
    bool isDefault = json.value(isDefaultKey).toBool(false);
    return Wallet::createFromValue(id, name, initTime, initAmount, isDefault);
}

QJsonObject WalletMapper::toJson(const Wallet& t)
{
    QJsonObject result = {
        { nameKey, t.name }
    };

    if (t.initTime.isValid()) {
        result.insert(initTimeKey, timeToValue(t.initTime));
        result.insert(initAmountKey, static_cast<int>(t.initAmount));
    }

    return result;
}

void WalletMapper::patch(Wallet& t, const QJsonObject& json)
{
    t.name = json.contains(nameKey) ? json[nameKey].toString() : t.name;
    t.initAmount = json.contains(initAmountKey) ? json[initAmountKey].toInt(0) : t.initAmount;
    t.initTime = json.contains(initTimeKey) ? valueToTime(json[initTimeKey]) : t.initTime;
}

QJsonObject WalletMapper::diff(const Wallet& from, const Wallet& to)
{
    QJsonObject result;

    if (from.name != to.name) {
        result.insert(nameKey, to.name);
    }

    if (from.initTime != to.initTime) {
        result.insert(initTimeKey, timeToValue(to.initTime));
    }

    if (from.initAmount != to.initAmount) {
        result.insert(initAmountKey, static_cast<int>(to.initAmount));
    }

    return result;
}
