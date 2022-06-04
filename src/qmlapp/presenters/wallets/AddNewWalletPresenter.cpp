#include "AddNewWalletPresenter.h"
#include "../../viewmodel/AmountVm.h"

AddNewWalletPresenter::AddNewWalletPresenter(AddNewWalletUseCaseUnq usecase)
    : QObject()
    , m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);
    m_vm = new WalletEditVm(this);
}

void AddNewWalletPresenter::add()
{
    if (m_vm->getName().isEmpty()) {
        qWarning() << "Wallet name shouldn't be empty";
        return;
    }
    if (m_usecase->add(m_vm->getName(), AmountVM::amountFromString(m_vm->getInitAmounnt()))) {
        emit close();
    }
}
