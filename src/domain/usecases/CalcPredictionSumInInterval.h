#pragma once

#include <cstdint>
#include <entities/Prediction.h>
#include <repos/IPredictionRepo.h>

class CalcPredictionSumInInterval {
public:
    CalcPredictionSumInInterval(IPredictionRepoPtr repo);

    Predictions getPredictionsForDay(const QString& categoryId, const QDate& date);
    Predictions getPredictionsForDayOverall(const QDate& date);
    int64_t calcPredictedAmountForDay(const QString& categoryId, const QDate& date);
    int64_t calcPredictedAmountForDayOverall(const QDate& date);

private:
    IPredictionRepoPtr m_repo;
};
