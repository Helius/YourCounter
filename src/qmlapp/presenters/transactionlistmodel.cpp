#include "transactionlistmodel.h"


TransactionListModel::TransactionListModel(ITransactionRepoPtr repo, QObject * parent)
    : QAbstractListModel(parent)
    , m_repo(repo)
{
    Q_ASSERT(repo);
    connect(repo.get(), &ITransactionRepo::dataChanged, this, [this](){
        emit layoutChanged();
    });
}

int TransactionListModel::rowCount(const QModelIndex &) const
{
    return m_repo->getTransactions().size();
}

QVariant TransactionListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(static_cast<size_t>(row) >= m_repo->getTransactions().size()) return QVariant();
    switch (role) {
    case Category:
        return m_repo->getTransactions().at(row).category.name;
    case Amount:
        return m_repo->getTransactions().at(row).amount;
    case Who:
        return "??";
    case Date:
        return m_repo->getTransactions().at(row).when.toString();
    case RawDate:
        return m_repo->getTransactions().at(row).when;
    }
    return QVariant();
}

QHash<int, QByteArray> TransactionListModel::roleNames() const
{
    return {
        { Roles::Category, "category"},
        { Roles::Amount, "amount"},
        { Roles::Date, "date"},
        { Roles::Who, "who"},
    };
}

TransactionSortedListModel::TransactionSortedListModel(ITransactionRepoPtr repo)
    : QSortFilterProxyModel(nullptr)
    , m_sourceModel(new TransactionListModel(repo, this))
{
    setSourceModel(m_sourceModel);
}

bool TransactionSortedListModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    return source_left.data(TransactionListModel::RawDate).toDateTime() <  source_right.data(TransactionListModel::RawDate).toDateTime();
}
