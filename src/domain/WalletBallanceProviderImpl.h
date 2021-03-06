#pragma once

#include <QObject>
#include <repos/IEntityRepo.h>
#include <repos/IWalletBallanceProvider.h>
#include <usecases/wallets/CalcWalletBallanceUsecase.h>

class WalletBallanceProviderImpl : public IWalletBallanceProvider {

    Q_OBJECT

public:
    explicit WalletBallanceProviderImpl(IEntityRepoPtr repo);

public:
    int64_t getWalletBallance(const WalletId& walletId) override;

private:
    void updateAll();
    void updateByTransaction(const Transaction& t);
    int64_t calcByWalletId(const QString& walletId);

private:
    IEntityRepoPtr m_repo;
    std::map<QString, int64_t> m_data;
};
