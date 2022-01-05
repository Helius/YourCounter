#include "TransactionListModel.h"

TransactionListModel::TransactionListModel(IEntityRepoPtr repo, QObject* parent)
    : QAbstractListModel(parent)
    , m_repo(repo)
{
    Q_ASSERT(m_repo);

    using UpdateMode = IRepoObserver::UpdateMode;
    connect(m_repo->transactions().get(), &IRepoObserver::dataChanged, this,
        [this](UpdateMode mode, size_t startIndex, size_t size) {
            switch (mode) {
            case UpdateMode::Changed:
                break;
            case UpdateMode::Inserted:
                break;
            case UpdateMode::Removed:
                break;
            }
            beginResetModel();
            qDebug() << "categories changed" << mode << startIndex << size;
            endResetModel();
        });
}

QString TransactionListModel::getCategoryName(const QString& id) const
{
    const auto& categories = m_repo->categories()->data();
    const auto it = std::find_if(categories.cbegin(), categories.cend(), [id](const auto& c) {
        return c.id == id;
    });
    return it == categories.cend() ? "Category not found" : it->name;
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
    case CategoryName:
        return getCategoryName(transaction.categoryId);
    case Amount:
        return QString::number(transaction.amount / 100) + "." + QString::number(abs(transaction.amount) % 100);
    case Who:
        return transaction.who;
    case Date:
        return transaction.when.toString();
    case RawDate:
        return transaction.when;
    case Comment:
        return transaction.comment;
    }
    return QVariant();
}

QHash<int, QByteArray> TransactionListModel::roleNames() const
{
    return {
        { Roles::CategoryName, "categoryName" },
        { Roles::Amount, "amount" },
        { Roles::Date, "date" },
        { Roles::Who, "who" },
        { Roles::Comment, "comment" },
    };
}

TransactionSortedListModel::TransactionSortedListModel(IEntityRepoPtr repo)
    : QSortFilterProxyModel(nullptr)
    , m_sourceModel(new TransactionListModel(repo, this))
{
    setSourceModel(m_sourceModel);
    setDynamicSortFilter(true);
    sort(0);
}

bool TransactionSortedListModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    return source_left.data(TransactionListModel::RawDate).toDateTime()
        < source_right.data(TransactionListModel::RawDate).toDateTime();
}
