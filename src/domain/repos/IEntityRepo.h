#pragma once

#include "ICRUDRepo.h"
#include <entities/Category.h>
#include <entities/Group.h>
#include <entities/Transaction.h>

using ITransactionRepo = ICRUDRepo<Transaction>;
using ICategoryRepo = ICRUDRepo<Category>;
using IGroupRepo = ICRUDRepo<Group>;

using ITransactionRepoUnq = std::unique_ptr<ITransactionRepo>;
using ICategoryRepoUnq = std::unique_ptr<ICategoryRepo>;
using IGroupRepoUnq = std::unique_ptr<IGroupRepo>;

class IEntityRepo {
public:
    virtual ITransactionRepoUnq& transactions() = 0;
    virtual ICategoryRepoUnq& categories() = 0;
    virtual IGroupRepoUnq& groups() = 0;
    virtual ~IEntityRepo() = default;
};

using IEntityRepoPtr = std::shared_ptr<IEntityRepo>;
