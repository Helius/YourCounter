#include "timelinetablemodel.h"
#include <QColor>
#include <QDateTime>
#include <QDebug>

#include <repos/itransactionrepo.h>

namespace  {

QDateTime colToDateTime(int ind)
{
    return QDateTime(QDate(2021, 1, 1), QTime(0,0,0)).addDays(ind);
}

}


TimeLineTableModel::TimeLineTableModel(ITransactionRepo * repo, QObject * parent)
    : QAbstractListModel(parent)
    , m_repo(repo)
{
}

int TimeLineTableModel::getColumnWidth(int column)
{
    if (colToDateTime(column).daysTo(QDateTime::currentDateTime()) == 0)
        return -1;
    return m_repo->hasDailyAmount(column) ? -1 : 0;
}

int TimeLineTableModel::rowCount(const QModelIndex & ) const
{
    return m_repo->getCategories().size();
}

int TimeLineTableModel::columnCount(const QModelIndex &) const
{
    return 365;
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
        resultColor.setAlpha((100 * abs(amount))/10000);
//        if (colToDateTime(col).daysTo(QDateTime::currentDateTime()) == 0) {
//            resultColor.setAlpha(resultColor.alpha()+30);
//        }
        return resultColor;
    }
    case Roles::Amount:
        return calcAmount(row, col);
    case Roles::Current:
        return colToDateTime(col).daysTo(QDateTime::currentDateTime()) == 0;
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

QVariant TimeLineTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Orientation::Vertical)
    {
        if(section < static_cast<int>(m_repo->getCategories().size())) {
            return m_repo->getCategories()[section];
        }
    }
    else
    {
        return colToDateTime(section).toString("dd MMM");
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
