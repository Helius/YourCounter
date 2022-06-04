#include "AddNewWalletUsecase.h"
#include <entities/Wallet.h>

AddNewWalletUseCase::AddNewWalletUseCase(IEntityRepoPtr repo)
    : m_repo(repo->wallets())
{
    Q_ASSERT(m_repo);
}

bool AddNewWalletUseCase::add(const QString& name, int64_t initAmount)
{
    if (name.isEmpty()) {
        qWarning() << "Name can't be empty";
        return false;
    }

    if (!checkNameUnique(name)) {
        qWarning() << "Wallet name already exist";
        return false;
    }

    m_repo->create(Wallet::createRequest(name, initAmount));

    return true;
}

bool AddNewWalletUseCase::checkNameUnique(const QString& name)
{
    return std::find_if(m_repo->data().cbegin(), m_repo->data().cend(), [name](const auto& w) {
        return w.name.toLower() == name.toLower();
    }) == m_repo->data().cend();
}
