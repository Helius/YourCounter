#pragma once

#include "IFirebaseRtDbApi.h"
#include <repos/IEntityRepo.h>

class EntityRepoImpl : public IEntityRepo {
public:
    EntityRepoImpl() = delete;
    EntityRepoImpl(const IFirebaseRtDbAPIPtr& api);

    // IEntityRepo interface
public:
    ITransactionRepoUnq& transactions() override { return m_transactions; };
    ICategoryRepoUnq& categories() override { return m_categories; };
    IGroupRepoUnq& groups() override { return m_groups; };

private:
    ITransactionRepoUnq m_transactions;
    ICategoryRepoUnq m_categories;
    IGroupRepoUnq m_groups;
};
