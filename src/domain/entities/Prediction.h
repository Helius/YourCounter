#pragma once

#include "interval.h"
#include <QDateTime>
#include <QString>
#include <set>

class PredictionTemplate;

class Prediction {
public:
    Prediction() = delete;
    Prediction(const QString& templateId, int64_t amount)
        : templateId(templateId)
        , amount(amount)
    {
    }
    operator bool() const { return amount != 0; }
    QString templateId;
    int64_t amount;
};

using Predictions = std::vector<Prediction>;

class PredictionTemplate {

public:
    QString id;
    QString categoryId;
    QDate start; // invalid means prediction for months (monthMask) without particular day
    uint monthMask; // empty means single prediction
    int64_t amount;
    QString comment;
    bool cumulative = false;

    PredictionTemplate() = delete;
    static PredictionTemplate createRequest(
        const QString& categoryId,
        const QDate& start,
        int monthMask,
        int64_t amount,
        bool cumulative,
        const QString& comment = QString())
    {
        Q_ASSERT(!categoryId.isEmpty());
        return PredictionTemplate(QString(), categoryId, start, monthMask, amount, cumulative, comment);
    }
    static PredictionTemplate createFromValue(
        const QString& id,
        const QString& categoryId,
        const QDate& start,
        int monthMask,
        int64_t amount,
        bool cumulative,
        const QString& comment = QString())
    {
        Q_ASSERT(!id.isEmpty());
        Q_ASSERT(!categoryId.isEmpty());
        return PredictionTemplate(id, categoryId, start, monthMask, amount, cumulative, comment);
    }

    PredictionTemplate(const PredictionTemplate& other) = default;
    PredictionTemplate& operator=(const PredictionTemplate&) = default;

    operator bool() const
    {
        return !id.isEmpty() && !categoryId.isEmpty() && amount != 0
            && ((monthMask != 0) || start.isValid());
    }

    bool operator==(const PredictionTemplate& other) const
    {
        return id == other.id;
    }

    Prediction getPredictionForDay(const QDate& date) const
    {
        if (!date.isValid()) {
            return Prediction(QString(), 0);
        }
        if (start.isValid()) {
            if (monthMask == 0 && date == start) {
                return Prediction(id, amount);
            } else if ((monthMask & (1 << (date.month() - 1))) && (date.day() == start.day())) {
                return Prediction(id, amount);
            }
        } else {
            if ((date.day() == date.daysInMonth()) && (monthMask & (1 << (date.month() - 1)))) {
                return Prediction(id, amount);
            }
        }
        return Prediction(QString(), 0);
    }

private:
    PredictionTemplate(
        const QString& id,
        const QString& categoryId,
        const QDate& start,
        int monthMask,
        int64_t amount,

        bool cumulative = false,
        const QString& comment = QString())
        : id(id)
        , categoryId(categoryId)
        , start(start)
        , monthMask(monthMask)
        , amount(amount)
        , comment(comment)
        , cumulative(cumulative)
    {
        Q_ASSERT(amount != 0);
        // invalid start need monthMask
        Q_ASSERT((monthMask != 0) || start.isValid());
    }
};