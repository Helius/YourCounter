#include "AddNewCategoryUsecase.h"

AddNewCategoryUseCase::AddNewCategoryUseCase(IEntityRepoPtr repo)
    : QObject()
    , m_repo(repo)
{
    Q_ASSERT(m_repo);
}

void AddNewCategoryUseCase::addCategory(Category c)
{
    Q_ASSERT(c.id.isEmpty());

    if (c.name.isEmpty()) {
        emit categoryInvalid(InvalidReason::EmptyName);
        return;
    }

    if (!checkGroupExist(c.groupId)) {
        emit categoryInvalid(InvalidReason::GroupNotFound);
        return;
    }

    c.name = c.name.toLower();

    //TODO: get future and wait
    m_repo->categories()->create(c);
    emit categoryAdded();
}

bool AddNewCategoryUseCase::checkNameUnique(const QString& name)
{
    const auto& cats = m_repo->categories()->data();
    const auto& result = std::find_if(cats.cbegin(), cats.cend(), [name](const auto& c) {
        return c.name.toLower() == name.toLower();
    });
    return result == cats.cend();
}

bool AddNewCategoryUseCase::checkGroupExist(const QString& groupId)
{
    const auto& groups = m_repo->groups()->data();
    return groups.cend() != std::find_if(groups.cbegin(), groups.cend(), [groupId](const auto& g) {
        return g.id == groupId;
    });
}
