#pragma once

#include <QDateTime>
#include <QString>
#include <entities/WalletId.h>

class Wallet {

public:
    QString id;
    QString name;
    QDateTime initTime;
    int64_t initAmount;
    bool isDefault = false;

    using IdType = WalletId;

    Wallet() = delete;
    static Wallet createRequest(const QString& name, const int64_t initAmount)
    {
        return Wallet({}, name, QDateTime::currentDateTime(), initAmount);
    }
    static Wallet createFromValue(const QString& id, const QString& name, const QDateTime closeTime, int64_t closeAmount, bool isDefault = false)
    {
        return Wallet(id, name, closeTime, closeAmount, isDefault);
    }

    bool operator==(const Wallet& other) const { return id == other.id; }
    operator bool() const { return !id.isEmpty() && !name.isEmpty(); }

private:
    Wallet(
        const QString& id,
        const QString& name,
        QDateTime closeTime,
        int64_t closeAmount,
        bool isDefault = false)
        : id(id)
        , name(name)
        , initTime(closeTime)
        , initAmount(closeAmount)
        , isDefault(isDefault)
    {
        Q_ASSERT(!name.isEmpty());
    };
};

class WalletInfo : public Wallet {
public:
    WalletInfo(const Wallet & w)
        : Wallet(w) {
        ballance = 0;
    }

public:
    int64_t ballance;
};

using Wallets = std::vector<Wallet>;
