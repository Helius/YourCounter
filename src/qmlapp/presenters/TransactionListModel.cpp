#include "TransactionListModel.h"

TransactionListModel::TransactionListModel(IEntityRepoPtr repo, QObject* parent)
    : QAbstractListModel(parent)
    , m_repo(repo)
{
    Q_ASSERT(repo);

    // TODO: connect to changes of transactions, categories, groups

    //    connect(repo.get(), IEntityRepo::, this, [this](){
    //        emit layoutChanged();
    //    });
}

int TransactionListModel::rowCount(const QModelIndex&) const
{
    return m_repo->transactions()->data().size();
}

QVariant TransactionListModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    if (static_cast<size_t>(row) >= m_repo->transactions()->data().size())
        return QVariant();
    auto transaction = m_repo->transactions()->data().at(row);

    switch (role) {
    case Category:
        return transaction.categoryId;
    case Amount:
        return QVariant::fromValue(transaction.amount);
    case Who:
        return transaction.who;
    case Date:
        return transaction.when.toString();
    case RawDate:
        return transaction.when;
    }
    return QVariant();
}

QHash<int, QByteArray> TransactionListModel::roleNames() const
{
    return {
        { Roles::Category, "category" },
        { Roles::Amount, "amount" },
        { Roles::Date, "date" },
        { Roles::Who, "who" },
    };
}

TransactionSortedListModel::TransactionSortedListModel(IEntityRepoPtr repo)
    : QSortFilterProxyModel(nullptr)
    , m_sourceModel(new TransactionListModel(repo, this))
{
    setSourceModel(m_sourceModel);
}

bool TransactionSortedListModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    return source_left.data(TransactionListModel::RawDate).toDateTime()
        < source_right.data(TransactionListModel::RawDate).toDateTime();
}
