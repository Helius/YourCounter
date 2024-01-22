#include "WalletListModel.h"
#include "../../viewmodel/AmountVm.h"

using namespace AmountVM;

WalletListModel::WalletListModel(IWalletBallanceProviderPtr ballanceProvider)
	: QAbstractListModel()
	, m_ballanceProvider(ballanceProvider)
{
	Q_ASSERT(m_ballanceProvider);

	connect(
		m_ballanceProvider.get(),
		&IWalletBallanceProvider::ballanceChanged,
		this,
		[this]()
		{
			emit dataChanged(
				index(0),
				index(m_ballanceProvider->walletsInfo().size() - 1),
				{Roles::CurrentAmount});
			emit defaultWalletTotalChanged();
		});

	connect(
		m_ballanceProvider.get(),
		&IWalletBallanceProvider::ballanceChanged,
		this,
		[this]()
		{
			emit dataChanged(
				createIndex(0, 0),
				createIndex(m_ballanceProvider->walletsInfo().size() - 1, 0));
			sort(0);
		});
}

void WalletListModel::clearSelection()
{
	constexpr int invalidId = -1;

	if (m_selectedInd != invalidId)
	{
		m_selectedInd = invalidId;
		emit dataChanged(
			index(0, 0),
			index(m_ballanceProvider->walletsInfo().size(), 0),
			{Roles::Selected});
		emit selectedWalletIdChanged();
	}
}

QString WalletListModel::selectedWalletId()
{
	if ((m_selectedInd < 0) ||
		(m_selectedInd >= static_cast<int>(m_ballanceProvider->walletsInfo().size())))
	{
		return QString();
	}
	return m_ballanceProvider->walletsInfo().at(m_selectedInd).id;
}

int WalletListModel::rowCount(const QModelIndex &) const
{
	return m_ballanceProvider->walletsInfo().size();
}

QVariant WalletListModel::data(const QModelIndex & index, int role) const
{
	size_t ind = static_cast<size_t>(index.row());

	if (ind > m_ballanceProvider->walletsInfo().size())
	{
		return QVariant();
	}

	const auto & wallet = m_ballanceProvider->walletsInfo().at(ind);

	switch (role)
	{
	case Name:
		return wallet.name;
	case CurrentAmount:
		return formatAmount(wallet.ballance);
	case Selected:
		return m_selectedInd == static_cast<int>(ind);
	}
	return QVariant();
}

QHash<int, QByteArray> WalletListModel::roleNames() const
{
	return {
		{Roles::Name, "roleName"},
		{Roles::CurrentAmount, "roleAmount"},
		{Roles::Selected, "roleSelected"}};
}

bool WalletListModel::setData(const QModelIndex & indx, const QVariant &, int role)
{
	size_t ind = indx.row();
	if (ind > m_ballanceProvider->walletsInfo().size())
	{
		return false;
	}

	if (role == Selected)
	{
		if (static_cast<size_t>(m_selectedInd) != ind)
		{
			const auto prevInd = m_selectedInd;
			m_selectedInd = ind;
			emit selectedWalletIdChanged();
			emit dataChanged(indx, indx, {Roles::Selected});
			emit dataChanged(index(prevInd), index(prevInd), {Roles::Selected});
			return true;
		}
	}
	return false;
}
