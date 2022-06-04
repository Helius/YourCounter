#pragma once

#include <repos/IEntityRepo.h>
#include <repos/IWalletBallanceProvider.h>

class TransferUseCase {

public:
    enum class TransferResult {
        Ok,
        BadSrcOrDstWalletId,
        SrcAndDstWalletsTheSame,
        AmountShouldBePositive,
        NotEnoughtMoneyOnSrc,
    };

    TransferUseCase(IEntityRepoPtr repo, IWalletBallanceProviderPtr ballanceProvider);

    TransferResult createTransfer(
        const WalletId& from,
        const WalletId& to,
        int64_t amount,
        const QString& comment = QString());

private:
    IEntityRepoPtr m_repo;
    IWalletBallanceProviderPtr m_ballanceProvider;
};

using TransferUseCaseUnq = std::unique_ptr<TransferUseCase>;
