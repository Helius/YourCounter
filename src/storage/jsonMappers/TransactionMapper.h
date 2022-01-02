#pragma once

#include "IJsonMapper.h"
#include <QJsonObject>
#include <entities/Transaction.h>

class TransactionMapper : public IJsonMapper<Transaction> {
public:
    Transaction fromJson(const QString& id, const QJsonObject& json) override;
    QJsonObject toJson(const Transaction& t) override;
    void patch(Transaction& t, const QJsonObject& json) override;
    QJsonObject diff(const Transaction& from, const Transaction& to) override;
};
