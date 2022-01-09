#include "MonthReportUsecase.h"

MonthReportUsecase::MonthReportUsecase(IEntityRepoPtr repo)
    : QObject()
    , m_repo(repo)
{
    Q_ASSERT(m_repo);
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

std::pair<QString, QString> MonthReportUsecase::groupCategoryNameById(const QString& id)
{
    const auto& categories = m_repo->categories()->data();
    const auto& categoryIt = std::find_if(categories.cbegin(), categories.cend(), [id](const auto cat) {
        return id == cat.id;
    });
    Q_ASSERT(categoryIt != categories.cend());
    const auto& groups = m_repo->groups()->data();
    const auto& groupIt = std::find_if(groups.cbegin(), groups.cend(),
        [id = categoryIt->groupId](const auto g) {
            return id == g.id;
        });
    Q_ASSERT(groupIt != groups.cend());
    return { groupIt->name, categoryIt->name };
}
