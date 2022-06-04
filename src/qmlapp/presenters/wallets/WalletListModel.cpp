#include "WalletListModel.h"
#include "../../viewmodel/AmountVm.h"

using namespace AmountVM;

WalletListModel::WalletListModel(IEntityRepoPtr repo, IWalletBallanceProviderPtr ballanceProvider)
    : QAbstractListModel()
    , m_repo(repo->wallets())
    , m_ballanceProvider(ballanceProvider)
{
    Q_ASSERT(m_repo);
    Q_ASSERT(m_ballanceProvider);

    connect(m_ballanceProvider.get(), &IWalletBallanceProvider::ballanceChanged, this, [this]() {
        emit dataChanged(index(0), index(m_repo->data().size() - 1), { Roles::CurrentAmount });
        emit defaultWalletTotalChanged();
    });

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
    constexpr int invalidId = -1;

    if (m_selectedInd != invalidId) {
        m_selectedInd = invalidId;
        emit dataChanged(index(0, 0), index(m_repo->data().size() - 1, 0), { Roles::Selected });
        emit selectedWalletIdChanged();
    }
}

QString WalletListModel::selectedWalletId()
{
    if ((m_selectedInd < 0) || (m_selectedInd >= static_cast<int>(m_repo->data().size()))) {
        return QString();
    }
    return m_repo->data().at(m_selectedInd).id;
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
        return formatAmount(m_ballanceProvider->getWalletBallance(WalletId(m_repo->data().at(ind).id)));
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
        { Roles::Selected, "roleSelected" }
    };
}

bool WalletListModel::setData(const QModelIndex& indx, const QVariant&, int role)
{
    size_t ind = indx.row();
    if (ind > m_repo->data().size()) {
        return false;
    }

    if (role == Selected) {
        if (static_cast<size_t>(m_selectedInd) != ind) {
            const auto prevInd = m_selectedInd;
            m_selectedInd = ind;
            emit selectedWalletIdChanged();
            emit dataChanged(indx, indx, { Roles::Selected });
            emit dataChanged(index(prevInd), index(prevInd), { Roles::Selected });
            return true;
        }
    }
    return false;
}

QString WalletListModel::defaultWalletTotal() const
{
    return formatAmount(m_ballanceProvider->getWalletBallance(WalletId()));
}
