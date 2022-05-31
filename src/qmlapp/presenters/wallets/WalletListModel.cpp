#include "WalletListModel.h"

WalletListModel::WalletListModel(IEntityRepoPtr repo)
    : QAbstractListModel()
    , m_repo(repo->wallets())
{
    Q_ASSERT(m_repo);

    using UpdateMode = IRepoObserver::UpdateMode;
    connect(m_repo.get(), &IRepoObserver::dataChanged,
        this,
        [this](UpdateMode mode, size_t startIndex, size_t size) {
            switch (mode) {
            case UpdateMode::Changed:
                qDebug() << "Changed" << mode << startIndex << size;
                emit dataChanged(createIndex(startIndex, 0), createIndex(startIndex + size - 1, 0));
                break;
            case UpdateMode::Inserted:
                beginInsertRows(QModelIndex(), startIndex, startIndex + size - 1);
                qDebug() << "Inserted" << mode << startIndex << size;
                endInsertRows();
                break;
            case UpdateMode::Removed:
                beginRemoveRows(QModelIndex(), startIndex, startIndex + size - 1);
                qDebug() << "Removed" << mode << startIndex << size;
                endRemoveRows();
                break;
            }
            sort(0);
        });
}

void WalletListModel::clearSelection()
{
    m_selectedInd = -1;
    emit dataChanged(index(0, 0), index(0, rowCount({}) - 1), { Selected });
}

int WalletListModel::rowCount(const QModelIndex&) const
{
    return m_repo->data().size();
}

QVariant WalletListModel::data(const QModelIndex& index, int role) const
{
    size_t ind = static_cast<size_t>(index.row());

    if (ind > m_repo->data().size()) {
        return QVariant();
    }

    switch (role) {
    case Name:
        return m_repo->data().at(ind).name;
    case CurrentAmount:
        return 12;
    case SourceCategoryName:
        return m_repo->data().at(ind).srcId.toString();
    case Selected:
        return m_selectedInd == static_cast<int>(ind);
    }
    return QVariant();
}

QHash<int, QByteArray> WalletListModel::roleNames() const
{
    return {
        { Roles::Name, "roleName" },
        { Roles::CurrentAmount, "roleAmount" },
        { Roles::SourceCategoryName, "roleCategoryName" },
        { Roles::Selected, "roleSelected" }
    };
}

bool WalletListModel::setData(const QModelIndex& index, const QVariant&, int role)
{
    size_t ind = index.row();
    if (ind > m_repo->data().size()) {
        return false;
    }

    if (role == Selected) {
        m_selectedInd = ind;
        return true;
    }

    return false;
}
