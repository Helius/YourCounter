#include "EditTransactionPresenter.h"

EditTransactionPresenter::EditTransactionPresenter(EditTransactionUsecaseUnq usecase)
    : QObject()
    , m_usecase(std::move(usecase))
    , m_vm(new TransactionEditFeildsVm(this))
{
}

void EditTransactionPresenter::apply()
{
    /*
    auto t = m_vm->buildTransaction();
    t.id = m_transactionId;
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
*/
}

void EditTransactionPresenter::setTransactionId(const QString& transactionId)
{
    m_transactionId = transactionId;
    auto t = m_usecase->loadTransaction(transactionId);
    //    m_vm->
}
