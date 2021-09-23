#include "timelinetablemodel.h"
#include <QColor>
#include <QDebug>
#include <algorithm>

#include <repos/itransactionrepo.h>
#include <repos/idatecolumnadapter.h>


TimeLineTableModel::TimeLineTableModel(ITransactionRepoUnq repo, std::shared_ptr<IDateColumnAdapter> dateAdapter)
    : QAbstractListModel()
    , m_repo(std::move(repo))
    , m_dateAdapter(dateAdapter)
{
    Q_ASSERT(m_repo);
    Q_ASSERT(m_dateAdapter);
    connect(m_repo.get(), &ITransactionRepo::dataChanged, this, [this](){
        emit headerDataChanged(Qt::Orientation::Vertical, 0, rowCount({})-1);
        emit headerDataChanged(Qt::Orientation::Horizontal, 0, columnCount({})-1);
        emit layoutChanged();
    });
}

int TimeLineTableModel::getColumnWidth(int column)
{
    if(m_dateAdapter->isCurrent(column))
        return -1;
    return m_repo->hasColumnAmount(column) ? -1 : 0;
}

int TimeLineTableModel::rowCount(const QModelIndex & ) const
{
    return m_repo->getCategories().size();
}

int TimeLineTableModel::columnCount(const QModelIndex &) const
{
    return m_dateAdapter->columnCount();
}

QVariant TimeLineTableModel::data(const QModelIndex & ind, int role) const
{
    if (!ind.isValid()) {
        return QVariant();
    }

    int row = ind.row();
    int col = ind.column();

    switch (role) {
    case Roles::Color: {
        float amount = m_repo->calcAmount(row, col);
        QColor spend(0xff, 0, 0);
        QColor earn(0, 0xff, 0);
        auto & resultColor = amount > 0 ? earn : spend;

        resultColor.setAlpha(amount > 0
                                 ? std::min(static_cast<int>(10+(100 * amount)/m_repo->max()), 100)
                                 : std::min(static_cast<int>(10+(100 * amount)/m_repo->min()), 100));
        if(amount == 0) {
            resultColor.setAlpha(0);
        }
        return resultColor;
    }
    case Roles::Amount:
        return calcAmount(row, col);
    case Roles::Current:
        return m_dateAdapter->isCurrent(col);
    }

    return QVariant();
}

QHash<int, QByteArray> TimeLineTableModel::roleNames() const
{
    return {
        {Roles::Color, "color"},
        {Roles::Amount, "amount"},
        {Roles::Current, "isCurrent"}
    };
}

QVariant TimeLineTableModel::headerData(int section, Qt::Orientation orientation, int /*role*/) const
{
    emit
    if(orientation == Qt::Orientation::Vertical)
    {
        if(section < static_cast<int>(m_repo->getCategories().size())) {
            return m_repo->getCategories()[section];
        }
    }
    else
    {
        return m_dateAdapter->columnName(section);
    }
    return QVariant();
}

QString TimeLineTableModel::calcAmount(int row, int col) const
{
    float amount = m_repo->calcAmount(row, col);

    if(abs(amount) > 0.01) {
        return QString::number(amount);
    }
    else
    {
        return QString();
    }
}
