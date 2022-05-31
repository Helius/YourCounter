#pragma once

#include <QDateTime>
#include <QString>
#include <entities/Category.h>

class WalletId {
public:
    explicit WalletId() = default;
    explicit WalletId(const QString& id)
        : m_id(id)
    {
    }

    operator bool() const { return !m_id.isEmpty(); }
    QString toString() const { return m_id; }

private:
    QString m_id;
};

class Wallet {

public:
    QString id;
    QString name;
    CategoryId srcId;
    QDateTime fixTime;
    int64_t fixedAmount;

    using IdType = WalletId;

    Wallet() = delete;
    static Wallet createRequest(const QString& name, const CategoryId srcId)
    {
        return Wallet({}, name, srcId, {}, 0);
    }
    static Wallet createFromValue(const QString& id, const QString& name, const CategoryId srcId, QDateTime closeTime, int64_t closeAmount)
    {
        return Wallet(id, name, srcId, closeTime, closeAmount);
    }

    bool operator==(const Wallet& other) const { return id == other.id; }
    operator bool() const { return !id.isEmpty() && !name.isEmpty(); }

private:
    Wallet(
        const QString& id,
        const QString& name,
        const CategoryId srcId,
        QDateTime closeTime,
        int64_t closeAmount)
        : id(id)
        , name(name)
        , srcId(srcId)
        , fixTime(closeTime)
        , fixedAmount(closeAmount)
    {
        Q_ASSERT(!name.isEmpty());
    };
};

using Wallets = std::vector<Wallet>;