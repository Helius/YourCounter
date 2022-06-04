#pragma once

#include <QDateTime>
#include <QString>
#include <entities/WalletId.h>

class Wallet {

public:
    QString id;
    QString name;
    QDateTime fixTime;
    int64_t fixedAmount;

    using IdType = WalletId;

    Wallet() = delete;
    static Wallet createRequest(const QString& name, const int64_t initAmount)
    {
        return Wallet({}, name, QDateTime::currentDateTime(), initAmount);
    }
    static Wallet createFromValue(const QString& id, const QString& name, const QDateTime closeTime, int64_t closeAmount)
    {
        return Wallet(id, name, closeTime, closeAmount);
    }

    bool operator==(const Wallet& other) const { return id == other.id; }
    operator bool() const { return !id.isEmpty() && !name.isEmpty(); }

private:
    Wallet(
        const QString& id,
        const QString& name,
        QDateTime closeTime,
        int64_t closeAmount)
        : id(id)
        , name(name)
        , fixTime(closeTime)
        , fixedAmount(closeAmount)
    {
        Q_ASSERT(!name.isEmpty());
    };
};

class WalletData : public Wallet {

public:
    int64_t ballance;
};

using Wallets = std::vector<Wallet>;