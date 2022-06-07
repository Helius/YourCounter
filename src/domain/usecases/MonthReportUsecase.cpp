#include "MonthReportUsecase.h"

MonthReportUsecase::MonthReportUsecase(IEntityRepoPtr repo)
    : QObject()
    , m_repo(repo)
{
    Q_ASSERT(m_repo);
    connect(m_repo->transactions().get(), &IRepoObserver::dataChanged, this, &MonthReportUsecase::amountsChanged);
}

MonthReportUsecase::CategoriesTotalAmount MonthReportUsecase::generateMonthReport(const QDate& monthDate)
{
    std::map<QString, int64_t> amountByCategory;
    for (const auto& transaction : m_repo->transactions()->data()) {
        if (transaction.when.date().month() == monthDate.month()) {
            amountByCategory[transaction.categoryId] += transaction.amount;
        }
    }
    CategoriesTotalAmount result;
    std::transform(amountByCategory.cbegin(), amountByCategory.cend(), std::back_inserter(result),
        [this](const auto& keyValue) {
            QString groupName;
            QString categoryName;
            std::tie(groupName, categoryName) = groupCategoryNameById(keyValue.first);
            return CategoryTotalAmount { groupName, categoryName, keyValue.second };
        });
    return result;
}

void MonthReportUsecase::calcEarnSpend(const QDate& monthDate)
{
    int64_t earn = 0;
    int64_t spend = 0;
    for (const auto& transaction : m_repo->transactions()->data()) {
        if (transaction.when.date().month() == monthDate.month()) {
            if (transaction.amount > 0) {
                earn += transaction.amount;
            } else {
                spend += transaction.amount;
            }
        }
    }
    emit earnSpendChanged(earn, spend);
}

std::pair<QString, QString> MonthReportUsecase::groupCategoryNameById(const QString& id)
{
    QString cName;
    QString gName;
    const auto categoryOpt = m_repo->categories()->find(id);
    if (categoryOpt) {
        cName = categoryOpt->name;
        const auto& groupOpt = m_repo->groups()->find(categoryOpt->groupId);
        Q_ASSERT(!!groupOpt);
        gName = groupOpt->name;
    }

    if (cName.isEmpty()) {
        const auto wallet = m_repo->wallets()->find(id);
        Q_ASSERT(!!wallet);
        cName = wallet->name;
        gName = "wallets";
    }

    return { gName, cName };
}
