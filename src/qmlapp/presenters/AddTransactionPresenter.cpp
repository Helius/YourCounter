#include "AddTransactionPresenter.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

AddTransactionPresenter::AddTransactionPresenter(AddNewTransactionUseCaseUnq usecase)
    : m_usecase(std::move(usecase))
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][.0-9]*"), this))
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
}

void AddTransactionPresenter::add()
{
    Transaction t = Transaction::createRequest(static_cast<int>(m_amount.toFloat() * 100), m_when, m_categoryId, m_who, m_coment);
    m_usecase->addTransaction(t);
}