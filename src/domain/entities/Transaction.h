#pragma once

#include <QDateTime>
#include <QString>

class Transaction {

public:
    QString id;
    int64_t amount = 0;
    QDateTime when;
    QString categoryId;
    QString who;
    QString comment;

    Transaction() = default;
    static Transaction createRequest(
        int64_t amount,
        const QDateTime& when,
        const QString& categoryId,
        const QString& who = QString(),
        const QString& comment = QString())
    {
        return Transaction(QString(), amount, when, categoryId, who, comment);
    }
    static Transaction createFromValue(
        const QString& id,
        int64_t amount,
        const QDateTime& when,
        const QString& categoryId,
        const QString& who = QString(),
        const QString& comment = QString())
    {
        Q_ASSERT(!id.isEmpty());
        return Transaction(id, amount, when, categoryId, who, comment);
    }

    Transaction(const Transaction& other) = default;
    Transaction& operator=(const Transaction&) = default;

    operator bool() const
    {
        return !id.isEmpty() && !categoryId.isEmpty() && amount != 0 && when.isValid();
    }

    bool operator==(const Transaction& other) const
    {
        return id == other.id
            && amount == other.amount
            && when == other.when
            && categoryId == other.categoryId
            && who == other.who
            && comment == other.comment;
    }

private:
    Transaction(
        const QString& id,
        int64_t amount,
        const QDateTime& when,
        const QString& categoryId,
        const QString& who = QString(),
        const QString& comment = QString())
        : id(id)
        , amount(amount)
        , when(when)
        , categoryId(categoryId)
        , who(who)
        , comment(comment)
    {
        Q_ASSERT(amount != 0);
    }
};

using Transactions = std::vector<Transaction>;
