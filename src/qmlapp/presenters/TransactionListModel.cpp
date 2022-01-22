#include "TransactionListModel.h"
#include "../viewmodel/AmountVm.h"

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
                qDebug() << "transactions Changed" << mode << startIndex << size;
                dataChanged(createIndex(startIndex, 0), createIndex(startIndex + size - 1, 0));
                break;
            case UpdateMode::Inserted:
                beginInsertRows(QModelIndex(), startIndex, startIndex + size - 1);
                qDebug() << "transactions Inserted" << mode << startIndex << size;
                endInsertRows();
                break;
            case UpdateMode::Removed:
                //TODO: beginRemoveRows
                beginResetModel();
                qDebug() << "transactions Removed" << mode << startIndex << size;
                endResetModel();
                break;
            }
            sort(0);
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

QString TransactionListModel::formatDate(const QDateTime& dateTime) const
{
    return dateTime.date().toString("dddd dd MMMM");
}

void TransactionListModel::updateSelectedAmount()
{
    m_selectedAmount = 0;
    const auto& transactions = m_repo->transactions()->data();
    for (const auto& index : m_selectedItems) {
        if (static_cast<size_t>(index) < transactions.size()) {
            m_selectedAmount += transactions[index].amount;
        }
    }
    emit selectedAmountChanged();
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
    case Id:
        return transaction.id;
    case CategoryName:
        return getCategoryName(transaction.categoryId);
    case Amount:
        return AmountVM::formatAmount(transaction.amount);
    case Who:
        return transaction.who;
    case Date:
        return formatDate(transaction.when);
    case RawDate:
        return transaction.when;
    case Comment:
        return transaction.comment;
    case Selected:
        return m_selectedItems.find(index.row()) != m_selectedItems.cend();
    }
    return QVariant();
}

QHash<int, QByteArray> TransactionListModel::roleNames() const
{
    return {
        { Roles::Id, "transactionId" },
        { Roles::CategoryName, "categoryName" },
        { Roles::Amount, "amount" },
        { Roles::Date, "date" },
        { Roles::Who, "who" },
        { Roles::Comment, "comment" },
        { Roles::Selected, "selected" },
    };
}

bool TransactionListModel::setData(const QModelIndex& index, const QVariant&, int role)
{
    if (role == Roles::Selected) {
        if (m_selectedItems.find(index.row()) != m_selectedItems.cend()) {
            m_selectedItems.erase(index.row());
        } else {
            m_selectedItems.insert(index.row());
        }
        emit dataChanged(index, index, { Roles::Selected });
        updateSelectedAmount();
        return true;
    }
    return false;
}

QString TransactionListModel::selectedAmountStr()
{
    return m_selectedAmount != 0 ? AmountVM::formatAmount(m_selectedAmount) : QString();
}

TransactionSortedListModel::TransactionSortedListModel(IEntityRepoPtr repo)
    : QSortFilterProxyModel(nullptr)
    , m_sourceModel(new TransactionListModel(repo, this))
{
    setSourceModel(m_sourceModel);
    setDynamicSortFilter(true);
    sort(0);
    connect(m_sourceModel, &TransactionListModel::selectedAmountChanged, this, &TransactionSortedListModel::selectedAmountChanged);
}

bool TransactionSortedListModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    return source_left.data(TransactionListModel::RawDate).toDateTime()
        < source_right.data(TransactionListModel::RawDate).toDateTime();
}
const QString TransactionSortedListModel::selectedAmount() const
{
    return m_sourceModel->selectedAmountStr();
}
