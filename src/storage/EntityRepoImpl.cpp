#include "EntityRepoImpl.h"
#include "CrudRepoImpl.h"
#include "jsonMappers/CategoryMapper.h"
#include "jsonMappers/GroupMappers.h"
#include "jsonMappers/TransactionMapper.h"
#include "jsonMappers/WalletMapper.h"

EntityRepoImpl::EntityRepoImpl(const IFirebaseRtDbAPIPtr& api)
{
    m_transactions = std::make_unique<CrudRepository<Transaction>>(
        "/transaction",
        api,
        std::make_shared<TransactionMapper>());

    m_categories = std::make_unique<CrudRepository<Category>>(
        "/categories",
        api,
        std::make_shared<CategoryMapper>());

    m_groups = std::make_unique<CrudRepository<Group>>(
        "/groups",
        api,
        std::make_shared<GroupMapper>());

    m_wallets = std::make_unique<CrudRepository<Wallet>>(
        "/wallets",
        api,
        std::make_shared<WalletMapper>());

    m_needLogin = api->needLogin();
}
