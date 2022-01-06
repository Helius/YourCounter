#include "PredictionMapper.h"
#include <QDateTime>

namespace {
QLatin1String amountKey("amount");
QLatin1String categoryIdKey("categoryId");
QLatin1String startKey("start");
QLatin1String commentKey("comment");
QLatin1String monthMaskKey("monthMask");
QLatin1String cumulativeKey("cumulative");
QLatin1String dateToStringFormat("yyyyMMdd");
}

Prediction PredictionMapper::fromJson(const QString& id, const QJsonObject& json)
{
    float amount = json.value(amountKey).toInt(0);
    QDate start = QDate::fromString(json.value(startKey).toString(), dateToStringFormat);
    QString categoryId = json.value(categoryIdKey).toString();
    int monthMask = json.value(monthMaskKey).toInt(0);
    bool cumulative = json.value(cumulativeKey).toBool(false);
    QString comment = json.value(commentKey).toString();
    return Prediction::createFromValue(
        id,
        categoryId,
        start,
        monthMask,
        amount,
        cumulative,
        comment);
}

QJsonObject PredictionMapper::toJson(const Prediction& p)
{
    return {
        { categoryIdKey, p.categoryId },
        { startKey, p.start.toString(dateToStringFormat) },
        { monthMaskKey, static_cast<int>(p.monthMask) },
        { amountKey, static_cast<int>(p.amount) },
        { cumulativeKey, p.cumulative },
        { commentKey, p.comment }
    };
}

void PredictionMapper::patch(Prediction& p, const QJsonObject& json)
{
    p.categoryId = json.contains(categoryIdKey) ? json.value(categoryIdKey).toString() : p.categoryId;
    p.start = json.contains(startKey) ? QDate::fromString(json.value(startKey).toString(), dateToStringFormat) : p.start;
    p.monthMask = json.contains(monthMaskKey) ? json.value(monthMaskKey).toInt(0) : p.monthMask;
    p.amount = json.contains(amountKey) ? json.value(amountKey).toInt() : p.amount;
    p.cumulative = json.contains(cumulativeKey) ? json.value(cumulativeKey).toBool(false) : p.cumulative;
    p.comment = json.contains(commentKey) ? json.value(commentKey).toString() : p.comment;
}

QJsonObject PredictionMapper::diff(const Prediction& from, const Prediction& to)
{
    QJsonObject result;

    if (to.categoryId != from.categoryId) {
        result.insert(categoryIdKey, to.categoryId);
    }
    if (to.start != from.start) {
        result.insert(startKey, to.start.toString(dateToStringFormat));
    }
    if (to.monthMask != from.monthMask) {
        result.insert(monthMaskKey, static_cast<int>(to.monthMask));
    }
    if (to.amount != from.amount) {
        result.insert(amountKey, static_cast<int>(to.amount));
    }
    if (to.cumulative != from.cumulative) {
        result.insert(cumulativeKey, to.cumulative);
    }
    if (to.comment != from.comment) {
        result.insert(commentKey, to.comment);
    }

    return result;
}
