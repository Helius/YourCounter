#include "NewTransferPresenter.h"
#include "../../viewmodel/AmountVm.h"

NewTransferPresenter::NewTransferPresenter(TransferUseCaseUnq usecase)
    : QObject()
    , m_usecase(std::move(usecase))
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][ ,0-9]*"), this))
{
    Q_ASSERT(m_usecase);
}

const QString& NewTransferPresenter::dstWallet() const
{
    return m_dstWallet;
}

void NewTransferPresenter::setdstWallet(const QString& newDstWallet)
{
    if (m_dstWallet == newDstWallet) {
        return;
    }
    m_dstWallet = newDstWallet;
    emit dstWalletChanged();
}

const QString& NewTransferPresenter::srcWallet() const
{
    return m_srcWallet;
}

void NewTransferPresenter::setSrcWallet(const QString& newSrcWallet)
{
    if (m_srcWallet == newSrcWallet) {
        return;
    }
    m_srcWallet = newSrcWallet;
    emit srcWalletChanged();
}

const QString& NewTransferPresenter::amount() const
{
    return m_amount;
}

void NewTransferPresenter::setAmount(const QString& newAmount)
{
    if (m_amount == newAmount) {
        return;
    }
    m_amount = newAmount;
    emit amountChanged();
}

bool NewTransferPresenter::add()
{

    const auto error = m_usecase->createTransfer(
        WalletId(m_srcWallet),
        WalletId(m_dstWallet),
        AmountVM::amountFromString(m_amount));

    if (error == TransferUseCase::TransferResult::Ok) {
        return true;
    }

    qWarning() << "Transfer create error";
    switch (error) {
    case TransferUseCase::TransferResult::AmountShouldBePositive:
        qWarning() << "Amount should be positive";
        break;
    case TransferUseCase::TransferResult::BadSrcOrDstWalletId:
        qWarning()
            << "Bad source or destination wallet, one of them should have valid id";
        break;
    case TransferUseCase::TransferResult::NotEnoughtMoneyOnSrc:
        qWarning()
            << "Not enought money on source wallet";
        break;
    case TransferUseCase::TransferResult::SrcAndDstWalletsTheSame:
        qWarning()
            << "Both wallets the same";
        break;
    default:
        break;
    }

    return false;
}
