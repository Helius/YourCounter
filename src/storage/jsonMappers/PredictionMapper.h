#pragma once

#include "IJsonMapper.h"
#include <QJsonObject>
#include <entities/Prediction.h>

class PredictionMapper : public IJsonMapper<PredictionTemplate> {
public:
    PredictionTemplate fromJson(const QString& id, const QJsonObject& json) override;
    QJsonObject toJson(const PredictionTemplate& p) override;
    void patch(PredictionTemplate& p, const QJsonObject& json) override;
    QJsonObject diff(const PredictionTemplate& from, const PredictionTemplate& to) override;
};
