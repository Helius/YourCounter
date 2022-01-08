#include "CalcPredictionSumInInterval.h"

CalcPredictionSumInInterval::CalcPredictionSumInInterval(IPredictionRepoPtr repo)
    : m_repo(repo)
{
    Q_ASSERT(m_repo);
}

Predictions CalcPredictionSumInInterval::getPredictionsForDay(const QString& categoryId, const QDate& date)
{
    Predictions result;
    for (const auto& pTemplate : m_repo->data()) {
        if (pTemplate.categoryId == categoryId) {
            if (auto p = pTemplate.getPredictionForDay(date)) {
                result.push_back(p);
            }
        }
    }
    return result;
}

Predictions CalcPredictionSumInInterval::getPredictionsForDayOverall(const QDate& date)
{
    Predictions result;
    for (const auto& pTemplate : m_repo->data()) {
        if (auto p = pTemplate.getPredictionForDay(date)) {
            result.push_back(p);
        }
    }
    return result;
}

int64_t CalcPredictionSumInInterval::calcPredictedAmountForDay(const QString& categoryId, const QDate& date)
{
    int64_t total = 0;
    for (const auto& pTemplate : m_repo->data()) {
        if (pTemplate.categoryId == categoryId) {
            if (auto p = pTemplate.getPredictionForDay(date)) {
                total += p.amount;
            }
        }
    }
    return total;
}

int64_t CalcPredictionSumInInterval::calcPredictedAmountForDayOverall(const QDate& date)
{
    int64_t total = 0;
    for (const auto& pTemplate : m_repo->data()) {
        if (auto p = pTemplate.getPredictionForDay(date)) {
            total += p.amount;
        }
    }
    return total;
}
