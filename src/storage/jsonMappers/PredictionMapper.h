#pragma once

#include "IJsonMapper.h"
#include <QJsonObject>
#include <entities/Prediction.h>

class PredictionMapper : public IJsonMapper<Prediction> {
public:
    Prediction fromJson(const QString& id, const QJsonObject& json) override;
    QJsonObject toJson(const Prediction& p) override;
    void patch(Prediction& p, const QJsonObject& json) override;
    QJsonObject diff(const Prediction& from, const Prediction& to) override;
};
