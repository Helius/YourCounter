#include "TransferUsecase.h"

TransferUseCase::TransferUseCase(IEntityRepoPtr repo, IWalletBallanceProviderPtr ballanceProvider)
    : m_repo(repo)
    , m_ballanceProvider(ballanceProvider)
{
    Q_ASSERT(m_repo);
    Q_ASSERT(m_ballanceProvider);
}

TransferUseCase::TransferResult TransferUseCase::createTransfer(
    const WalletId& from,
    const WalletId& to,
    int64_t amount,
    QDate date,
    const QString& comment)
{
    if (amount <= 0) {
        return TransferResult::AmountShouldBePositive;
    }

    if (from == to) {
        return TransferResult::SrcAndDstWalletsTheSame;
    }

    auto src = m_repo->wallets()->find(from.toString());
    auto dst = m_repo->wallets()->find(to.toString());

    if (!src && !dst) {
        return TransferResult::BadSrcOrDstWalletId;
    }

    if (src == dst) {
        return TransferResult::SrcAndDstWalletsTheSame;
    }

    if (m_ballanceProvider->getWalletBallance(from) < amount) {
        return TransferResult::NotEnoughtMoneyOnSrc;
    }

    int days = date.daysTo(QDate::currentDate());
    if (days < 0 || days > 60) {
        return TransferResult::DateSeemsNotCorrect;
    }

    Transaction t = Transaction::createRequest(
        -amount,
        QDateTime(date, QTime::currentTime()),
        to.toString(),
        from,
        "pc",
        "transfer: " + comment);

    m_repo->transactions()->create(t);

    return TransferResult::Ok;
}
