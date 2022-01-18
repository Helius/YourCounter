#include "EditTransactionPresenter.h"
#include "../viewmodel/AmountVm.h"

EditTransactionPresenter::EditTransactionPresenter(EditTransactionUsecaseUnq usecase, const QString& transactionId)
    : QObject()
    , m_usecase(std::move(usecase))
    , m_transactionId(transactionId)
{
    Q_ASSERT(m_usecase);
    Q_ASSERT(!transactionId.isEmpty());

    auto t = m_usecase->loadTransaction(transactionId);
    auto transaction = std::get<0>(t);
    m_origTime = transaction.when;
    m_categoryId = transaction.categoryId;
    QString categoryName = std::get<1>(t);

    m_vm = new TransactionEditFeildsVm(
        categoryName,
        m_origTime.date(),
        transaction.who,
        AmountVM::formatAmount(transaction.amount),
        transaction.comment, this);
}

void EditTransactionPresenter::apply()
{
    Transaction t = Transaction::createFromValue(
        m_transactionId,
        AmountVM::amountFromString(m_vm->amount()),
        //TODO: bullshit, not presenter's responsibility
        m_vm->when() != m_origTime.date() ? QDateTime(m_vm->when(), QTime::currentTime()) : m_origTime,
        m_vm->categoryId().isEmpty() ? m_categoryId : m_vm->categoryId(),
        m_vm->who(),
        m_vm->comment());

    switch (m_usecase->applyChanges(t)) {
    case EditTransactionUsecase::EditError::BadAmount:
        qDebug() << "Error: bad amount";
        break;
    case EditTransactionUsecase::EditError::BadDate:
        qDebug() << "Error: bad date";
        break;
    case EditTransactionUsecase::EditError::BadOwner:
        qDebug() << "Error: bad owner";
        break;
    case EditTransactionUsecase::EditError::CategoryNotFound:
        qDebug() << "Error: category not found";
        break;
    case EditTransactionUsecase::EditError::TransactionIdDiffer:
        qDebug() << "Error: transaction id changed";
        break;
    case EditTransactionUsecase::EditError::Ok:
        qDebug() << "Ok";
        emit closePopup();
        break;
    }
}

EditTransactionBuilder::EditTransactionBuilder(EditTransactionUsecaseUnq usecase)
    : m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);
}

EditTransactionPresenterUnq EditTransactionBuilder::build(const QString& transactionId)
{
    return std::make_unique<EditTransactionPresenter>(std::move(m_usecase), transactionId);
}
