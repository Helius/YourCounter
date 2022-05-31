#include "AddNewWalletUsecase.h"
#include <entities/Wallet.h>

AddNewWalletUseCase::AddNewWalletUseCase(IEntityRepoPtr repo)
    : m_repo(repo->wallets())
{
    Q_ASSERT(m_repo);
}

void AddNewWalletUseCase::add(const QString& name, const CategoryId srcId)
{
    if (!srcId) {
        emit error("Source category id mustn't be empty");
        return;
    }

    if (!checkNameUnique(name)) {
        emit error("Wallet name already exist");
        return;
    }

    m_repo->create(Wallet::createRequest(name, srcId));
}

bool AddNewWalletUseCase::checkNameUnique(const QString& name)
{
    return std::find_if(m_repo->data().cbegin(), m_repo->data().cend(), [name](const auto& w) {
        return w.name.toLower() == name.toLower();
    }) != m_repo->data().cend();
}
