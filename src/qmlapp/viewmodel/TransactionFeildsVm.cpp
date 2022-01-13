#include "TransactionFeildsVm.h"
#include "AmountVm.h"
#include <QRegularExpression>

TransactionEditFeildsVm::TransactionEditFeildsVm(const Transaction& t, QObject* parent)
    : QObject(parent)
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][.0-9]*"), this))
{
    setTransaction(t);
}

TransactionEditFeildsVm::TransactionEditFeildsVm(QObject* parent)
    : QObject(parent)
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][.0-9]*"), this))
{
}

Transaction TransactionEditFeildsVm::buildTransaction()
{
    return Transaction::createRequest(static_cast<int>(m_amount.toFloat() * 100), m_when, m_categoryId, m_who, m_coment);
}

void TransactionEditFeildsVm::setTransaction(const Transaction& t)
{
    m_categoryId = t.categoryId;
    emit categoryIdChanged();

    m_when = t.when;
    emit whenChanged();

    m_who = t.who;
    emit whoChanged();

    m_amount = AmountVM::formatAmount(t.amount);
    emit amountChanged();

    m_coment = t.comment;
    emit comentChanged();
}
