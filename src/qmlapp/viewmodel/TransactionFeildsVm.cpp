#include "TransactionFeildsVm.h"
#include "AmountVm.h"
#include <QRegularExpression>

TransactionEditFeildsVm::TransactionEditFeildsVm(QObject* parent)
    : QObject(parent)
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][.0-9]*"), this))
{
}

void TransactionEditFeildsVm::setCategory(const QString& category)
{
    if (m_category != category) {
        m_category = category;
        emit categoryChanged();
    }
}

void TransactionEditFeildsVm::setWhen(const QDateTime& when)
{
    if (m_when != when) {
        m_when = when;
        emit whenChanged();
    }
}

void TransactionEditFeildsVm::setWho(const QString& who)
{
    if (m_who != who) {
        m_who = who;
        emit whoChanged();
    }
}

void TransactionEditFeildsVm::setAmount(const QString& amount)
{
    if (m_amount != amount) {
        m_amount = amount;
        emit amountChanged();
    }
}

void TransactionEditFeildsVm::setComment(const QString& comment)
{
    if (m_comment != comment) {
        m_comment = comment;
        emit commentChanged();
    }
}

//void TransactionEditFeildsVm::setTransaction(const Transaction& t)
//{
//    m_category = t.category;
//    emit categoryChanged();

//    m_when = t.when;
//    emit whenChanged();

//    m_who = t.who;
//    emit whoChanged();

//    m_amount = AmountVM::formatAmount(t.amount);
//    emit amountChanged();

//    m_coment = t.comment;
//    emit comentChanged();
//}
