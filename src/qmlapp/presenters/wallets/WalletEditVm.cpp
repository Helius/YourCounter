#include "WalletEditVm.h"
#include <QRegularExpression>

WalletEditVm::WalletEditVm(QObject* parent)
    : QObject { parent }
    , m_amountValidator(new QRegularExpressionValidator(QRegularExpression("^[-0-9][ ,0-9]*"), this))
{
}

WalletEditVm::WalletEditVm(const Wallet& w)
{
    m_name = w.name;
}
