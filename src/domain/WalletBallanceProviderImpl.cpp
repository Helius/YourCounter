#include "WalletBallanceProviderImpl.h"
#include "usecases/wallets/CalcWalletBallanceUsecase.h"

WalletBallanceProviderImpl::WalletBallanceProviderImpl(IEntityRepoPtr repo)
	: IWalletBallanceProvider()
	, m_repo(std::move(repo))
{
	Q_ASSERT(m_repo);

	// connect(
	// 	m_repo->transactions().get(),
	// 	&IRepoObserver::dataChanged,
	// 	this,
	// 	[this](IRepoObserver::UpdateMode, size_t, size_t)
	// 	{
	// 		// TODO: recalc certain wallet ballace
	// 		updateAll();
	// 	});
	updateAll();
}

int64_t WalletBallanceProviderImpl::getWalletBallance(const WalletId & walletId)
{
	int64_t amount = 0;
	const auto & wallet = m_repo->wallets()->find(walletId.toString());
	if (wallet)
	{
		amount = wallet->initAmount;
	}
	return amount + m_data[walletId.toString()];
}

const std::vector<WalletInfo> & WalletBallanceProviderImpl::walletsInfo()
{
	return m_wallets;
}

void WalletBallanceProviderImpl::updateAll()
{
	m_data.clear();

	m_wallets.clear();
	const auto wallets = m_repo->wallets()->data();
	for (const auto & w : wallets)
	{
		m_wallets.push_back(WalletInfo(w));
	}

	auto defaultWallet = std::find_if(
		m_wallets.begin(),
		m_wallets.end(),
		[](const auto & w)
		{
			return w.isDefault;
		});

	Q_ASSERT(defaultWallet != m_wallets.end());

	std::iter_swap(m_wallets.begin(), defaultWallet);
	
	qDebug() << "my wallets:";
	for (const auto & w: m_wallets) {
		qDebug() << "wallet " << w.name << w.id;
	}
	
	for (const auto & t : m_repo->transactions()->data())
	{
		m_data[t.walletId.toString()] += t.amount;

		if (auto it = std::find_if(
				wallets.begin(),
				wallets.end(),
				[t](const auto & wd)
				{
					return wd.id == t.categoryId;
				});
			it != wallets.cend())
		{
			auto srcWIt = std::find_if(
				m_wallets.cbegin(),
				m_wallets.cend(),
				[t](const auto & srcW)
				{
					return srcW.id == t.walletId.toString();
				});
			
			auto srcName = srcWIt != m_wallets.cend() ? srcWIt->name : "Unknown";

			qDebug() << "Transfer: " << t.amount / 100 << ", from " << srcName << " to" << it->name;
			m_data[it->id] += -t.amount;
		}
	}

	for (auto & w : m_wallets)
	{
		w.ballance = w.initAmount + m_data[w.id];
		if (w.isDefault)
		{
			w.ballance += m_data[QString()];
		}
	}

	for (auto it = m_data.begin(); it != m_data.end(); ++it)
	{
		auto walletIt = std::find_if(
				m_wallets.cbegin(),
				m_wallets.cend(),
				[it](const auto & w)
				{
					return w.id == it->first;
				});
		if (walletIt != m_wallets.cend())
		{
			qDebug() << "wallter_id validated: " << walletIt->name;
		}
		else
		{
			qCritical() << "found orthan wallet_id " << it->first << ", amount " << it->second;
		}
	}

	emit ballanceChanged();
}
