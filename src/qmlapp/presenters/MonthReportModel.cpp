#include "MonthReportModel.h"
#include "../viewmodel/AmountVm.h"

MonthReportModel::MonthReportModel(MonthReportUsecaseUnq usecase)
    : QAbstractListModel()
    , m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);
    m_amounts = m_usecase->generateMonthReport(QDate::currentDate());
    connect(m_usecase.get(), &MonthReportUsecase::amountsChanged, [this]() {
        beginResetModel();
        m_amounts = m_usecase->generateMonthReport(QDate::currentDate());
        endResetModel();
    });
}

int MonthReportModel::rowCount(const QModelIndex&) const
{
    return m_amounts.size();
}

QVariant MonthReportModel::data(const QModelIndex& index, int role) const
{
    size_t row = static_cast<size_t>(index.row());
    if (row >= m_amounts.size()) {
        return QVariant();
    }
    switch (role) {
    case Roles::GroupName:
        return m_amounts.at(row).groupName;
    case Roles::CategoryName:
        return m_amounts.at(row).categoryName;
    case Roles::TotalAmount:
        return AmountVM::formatAmount(m_amounts.at(row).totalAmount);
    }
    return QVariant();
}

QHash<int, QByteArray> MonthReportModel::roleNames() const
{
    return {
        { Roles::GroupName, "groupName" },
        { Roles::CategoryName, "categoryName" },
        { Roles::TotalAmount, "totalAmount" },
    };
}

MonthReportSortedModel::MonthReportSortedModel(MonthReportUsecaseUnq usecase)
    : QSortFilterProxyModel()
    , m_sourceModel(new MonthReportModel(std::move(usecase)))
{
    m_sourceModel->setParent(this);
    setSortRole(MonthReportModel::Roles::GroupName);
    sort(0);
    setSourceModel(m_sourceModel);
}
