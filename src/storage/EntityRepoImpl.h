#pragma once

#include "IFirebaseRtDbApi.h"
#include <repos/IEntityRepo.h>

class EntityRepoImpl : public IEntityRepo {
public:
    EntityRepoImpl() = delete;
    EntityRepoImpl(const IFirebaseRtDbAPIPtr& api);

    // IEntityRepo interface
public:
    const ITransactionRepoUnq& transactions() const override { return m_transactions; };
    const ICategoryRepoUnq& categories() const override { return m_categories; };
    const IGroupRepoUnq& groups() const override { return m_groups; };
    const IWalletRepoUnq& wallets() const override { return m_wallets; };
    bool needLogin() const override { return m_needLogin; }

private:
    ITransactionRepoUnq m_transactions;
    ICategoryRepoUnq m_categories;
    IGroupRepoUnq m_groups;
    IWalletRepoUnq m_wallets;
    bool m_needLogin = false;
};
