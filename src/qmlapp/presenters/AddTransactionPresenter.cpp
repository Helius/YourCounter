#include "AddTransactionPresenter.h"
#include "../viewmodel/AmountVm.h"

AddTransactionPresenter::AddTransactionPresenter(AddNewTransactionUseCaseUnq usecase)
    : m_usecase(std::move(usecase))
    , m_vm(new TransactionEditFeildsVm(this))
{
    Q_ASSERT(m_usecase);

    connect(m_usecase.get(), &AddNewTransactionUseCase::transactionInvalid,
        this, [](AddNewTransactionUseCase::InvalidReason r) {
            switch (r) {
            case AddNewTransactionUseCase::InvalidReason::ZerroAmount:
                qDebug() << "bad amount";
                break;
            case AddNewTransactionUseCase::InvalidReason::EmptyCategory:
                qDebug() << "empty category";
                break;
            case AddNewTransactionUseCase::InvalidReason::CategoryNotFound:
                qDebug() << "category not found";
                break;
            case AddNewTransactionUseCase::InvalidReason::DateInvalid:
                qDebug() << "date invalid";
                break;
            case AddNewTransactionUseCase::InvalidReason::DateFarInTheFuture:
                qDebug() << "date far in the future";
                break;
            case AddNewTransactionUseCase::InvalidReason::DateFarInThePast:
                qDebug() << "date far in the past";
                break;
            }
        });

    connect(m_usecase.get(), &AddNewTransactionUseCase::transactionAdded,
        this, &AddTransactionPresenter::closePopup);

    m_vm->setComent(QString());
}

void AddTransactionPresenter::apply()
{
    auto t = Transaction::createRequest(
        AmountVM::amountFromString(m_vm->amount()),
        QDateTime(m_vm->when(), QTime::currentTime()),
        m_vm->categoryId(),
        WalletId(m_vm->walletId()),
        m_vm->who(),
        m_vm->comment());
    m_usecase->addTransaction(t);
}
