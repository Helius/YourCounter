#pragma once

#include <QDateTime>
#include <QString>
#include <set>

class Prediction {

public:
    QString id;
    QString categoryId;
    QDate start; // invalid means prediction for months (monthMask) without particular day
    uint monthMask;
    int64_t amount;
    QString comment;
    bool cumulative = false;

    Prediction() = delete;
    static Prediction createRequest(
        const QString& categoryId,
        const QDate& start,
        int monthMask,
        int64_t amount,
        bool cumulative,
        const QString& comment = QString())
    {
        Q_ASSERT(!categoryId.isEmpty());
        return Prediction(QString(), categoryId, start, monthMask, amount, cumulative, comment);
    }
    static Prediction createFromValue(
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
        return Prediction(id, categoryId, start, monthMask, amount, cumulative, comment);
    }

    Prediction(const Prediction& other) = default;
    Prediction& operator=(const Prediction&) = default;

    operator bool() const
    {
        return !id.isEmpty() && !categoryId.isEmpty() && amount != 0
            && ((monthMask != 0) || start.isValid());
    }

    bool operator==(const Prediction& other) const
    {
        return id == other.id;
    }

private:
    Prediction(
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

using Predictions = std::vector<Prediction>;
