#include "addtransactionbuttonpresenter.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

AddTransactionButtonPresenter::AddTransactionButtonPresenter(
    ITransactionRepoPtr repo,
    AddNewTransactionUseCaseUnq usecase)
    : m_repo(repo)
    , m_usecase(std::move(usecase))
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][0-9]*"), this))
{
    Q_ASSERT(m_repo);
    Q_ASSERT(m_usecase);

    connect(m_usecase.get(), &AddNewTransactionUseCase::transactionInvalid, this, [](){});
    connect(m_usecase.get(), &AddNewTransactionUseCase::isItNewCategory, this, [](){
        return true;
    });
}

void AddTransactionButtonPresenter::add()
{
    qDebug() << m_amount;
    qDebug() << m_category;
    qDebug() << m_coment;
    qDebug() << m_when;
    qDebug() << m_who;
}

