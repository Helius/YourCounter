#include "MonthReportModel.h"
#include "../viewmodel/AmountVm.h"

MonthReportModel::MonthReportModel(MonthReportUsecaseUnq usecase)
    : QAbstractListModel()
    , m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);

    connect(m_usecase.get(), &MonthReportUsecase::amountsChanged, [this]() {
        beginResetModel();
        m_amounts = m_usecase->generateMonthReport(calcReportMonth());
        endResetModel();
        updateTotal();
    });

    m_amounts = m_usecase->generateMonthReport(calcReportMonth());
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

int MonthReportModel::monthIndex() const
{
    return m_monthIndex;
}

void MonthReportModel::setMonthIndex(int newMonthIndex)
{
    if (m_monthIndex == newMonthIndex || newMonthIndex > QDate::currentDate().month())
        return;
    m_monthIndex = newMonthIndex;
    emit monthIndexChanged();
    beginResetModel();
    m_amounts = m_usecase->generateMonthReport(calcReportMonth());
    endResetModel();
    updateTotal();
}

QDate MonthReportModel::calcReportMonth() const
{
    const auto now = QDate::currentDate();
    if (now.month() >= m_monthIndex) {
        return QDate(now.year(), m_monthIndex, 1);
    } else {
        return now;
    }
}

void MonthReportModel::updateTotal()
{
    int64_t earn = 0;
    int64_t spend = 0;
    int64_t diff = 0;

    for (const auto& a : m_amounts) {
        if (a.groupName != "wallets") {
            if (a.totalAmount > 0) {
                earn += a.totalAmount;
            } else {
                spend += -a.totalAmount;
            }
        }
    }
    diff = earn - spend;
    emit numbersChanged(earn, spend, diff);
}

MonthReportSortedModel::MonthReportSortedModel(MonthReportUsecaseUnq usecase)
    : QSortFilterProxyModel()
    , m_sourceModel(new MonthReportModel(std::move(usecase)))
{
    m_sourceModel->setParent(this);
    setSortRole(MonthReportModel::Roles::GroupName);
    sort(0);
    setSourceModel(m_sourceModel);
    connect(m_sourceModel, &MonthReportModel::monthIndexChanged, this, &MonthReportSortedModel::monthIndexChanged);
    connect(m_sourceModel, &MonthReportModel::numbersChanged, this, [this](int64_t earn, int64_t spend, int64_t diff) {
        m_earn = AmountVM::formatAmount(earn);
        m_spend = AmountVM::formatAmount(spend);
        m_diff = AmountVM::formatAmount(diff);
        emit numbersChanged();
    });
    m_sourceModel->updateTotal();
}

int MonthReportSortedModel::monthIndex() const
{
    return static_cast<MonthReportModel*>(sourceModel())->monthIndex();
}

void MonthReportSortedModel::setMonthIndex(int newMonthIndex)
{
    return static_cast<MonthReportModel*>(sourceModel())->setMonthIndex(newMonthIndex);
}
