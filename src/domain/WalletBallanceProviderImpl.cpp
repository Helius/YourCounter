#include "WalletBallanceProviderImpl.h"
#include "usecases/wallets/CalcWalletBallanceUsecase.h"

WalletBallanceProviderImpl::WalletBallanceProviderImpl(IEntityRepoPtr repo)
    : IWalletBallanceProvider()
    , m_repo(std::move(repo))
{
    Q_ASSERT(m_repo);

    connect(m_repo->transactions().get(), &IRepoObserver::dataChanged, this,
        [this](IRepoObserver::UpdateMode, size_t, size_t) {
            //            if (size > 1) {
            //                updateAll();
            //            }
            //            if (mode == IRepoObserver::UpdateMode::Inserted
            //                || mode == IRepoObserver::UpdateMode::Changed) {
            //                updateByTransaction(m_repo->transactions()->data().at(startIndex));
            //            } else {
            updateAll();
            //            }
        });
    updateAll();
}

int64_t WalletBallanceProviderImpl::getWalletBallance(const WalletId& walletId)
{
    int64_t amount = 0;
    const auto& wallet = m_repo->wallets()->find(walletId.toString());
    if (wallet) {
        amount = wallet->fixedAmount;
    }
    return amount + m_data[walletId.toString()];
}

void WalletBallanceProviderImpl::updateAll()
{
    m_data.clear();

    for (const auto& t : m_repo->transactions()->data()) {

        m_data[t.walletId.toString()] += t.amount;

        const auto wallets = m_repo->wallets()->data();
        if (auto it = std::find_if(wallets.begin(), wallets.end(), [t](const auto& wd) {
                return wd.id == t.categoryId;
            });
            it != wallets.cend()) {
            m_data[it->id] += -t.amount;
        }
    }

    emit ballanceChanged();
}

void WalletBallanceProviderImpl::updateByTransaction(const Transaction& t)
{
    const auto srcId = t.walletId;
    const auto dstId = t.categoryId;
    std::vector<QString> walletIds;

    walletIds.push_back(srcId.toString());
    walletIds.push_back(dstId);

    for (const auto& id : walletIds) {
        m_data[id] += calcByWalletId(id);
    }
    emit ballanceChanged();
}

int64_t WalletBallanceProviderImpl::calcByWalletId(const QString& walletId)
{
    int64_t amount = 0;

    for (const auto& t : m_repo->transactions()->data()) {
        if (t.walletId.toString() == walletId) {
            amount += t.amount;
        } else if (t.categoryId == walletId) {
            amount += -t.amount;
        }
    }
    return amount;
}
