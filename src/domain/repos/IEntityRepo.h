#pragma once

#include "ICRUDRepo.h"
#include <entities/Category.h>
#include <entities/Group.h>
#include <entities/transaction.h>

using ITransactionRepo = ICRUDRepo<Transaction>;
using ICategoryRepo = ICRUDRepo<Category>;
using IGroupRepo = ICRUDRepo<Group>;

using ITransactionRepoUnq = std::unique_ptr<ITransactionRepo>;
using ICategoryRepoUnq = std::unique_ptr<ICategoryRepo>;
using IGroupRepoUnq = std::unique_ptr<IGroupRepo>;

struct IEntityRepo {
    ITransactionRepoUnq transactions;
    ICategoryRepoUnq categories;
    IGroupRepoUnq groups;
};

using IEntityRepoPtr = std::shared_ptr<IEntityRepo>;
