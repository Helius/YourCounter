#include "TransactionFeildsVm.h"
#include "AmountVm.h"
#include <QRegularExpression>

TransactionEditFeildsVm::TransactionEditFeildsVm(QObject* parent)
    : QObject(parent)
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][ .,0-9]*"), this))
{
}

TransactionEditFeildsVm::TransactionEditFeildsVm(
    const QString& category,
    const QDate& when,
    const QString& who,
    const QString& amount,
    const WalletId& walletId,
    const QString& comment,
    QObject* parent)
    : QObject(parent)
    , m_category(category)
    , m_when(when)
    , m_who(who)
    , m_amount(amount)
    , m_walletId(walletId.toString())
    , m_comment(comment)
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][ .,0-9]*"), this))
{
}

QDate TransactionEditFeildsVm::when() const
{
    return m_when;
}

QString TransactionEditFeildsVm::who() const
{
    return m_who;
}

QString TransactionEditFeildsVm::amount() const
{
    return m_amount;
}

QString TransactionEditFeildsVm::comment() const
{
    return m_comment;
}

QString TransactionEditFeildsVm::categoryId() const
{
    return m_categoryId;
}

QString TransactionEditFeildsVm::walletId() const
{
    return m_walletId;
}

QString TransactionEditFeildsVm::category() const
{
    return m_category;
}

void TransactionEditFeildsVm::setAmount(const QString& amount)
{
    if (m_amount == amount)
        return;

    m_amount = amount;
    emit amountChanged();
}

void TransactionEditFeildsVm::setComent(const QString& comment)
{
    if (m_comment == comment)
        return;

    m_comment = comment;
    emit commentChanged();
}

void TransactionEditFeildsVm::setWho(const QString& who)
{
    if (m_who == who)
        return;

    m_who = who;
    emit whoChanged();
}

void TransactionEditFeildsVm::setWhen(const QDate& when)
{
    if (m_when == when)
        return;

    m_when = when;
    emit whenChanged();
}

void TransactionEditFeildsVm::setCategoryId(const QString& categoryId)
{
    if (m_categoryId == categoryId) {
        return;
    }

    m_categoryId = categoryId;
    emit categoryIdChanged();
}

void TransactionEditFeildsVm::setWalletId(const QString& walletId)
{
    if (m_walletId == walletId) {
        return;
    }
    m_walletId = walletId;
    emit walletIdChanged();
}
