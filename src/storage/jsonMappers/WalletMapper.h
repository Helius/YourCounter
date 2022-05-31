#pragma once
#include "IJsonMapper.h"
#include <QJsonObject>
#include <entities/Wallet.h>

class WalletMapper : public IJsonMapper<Wallet> {
public:
    Wallet fromJson(const QString& id, const QJsonObject& json) override;
    QJsonObject toJson(const Wallet& t) override;
    void patch(Wallet& t, const QJsonObject& json) override;
    QJsonObject diff(const Wallet& from, const Wallet& to) override;
};