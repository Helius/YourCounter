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

    if (!checkNameUnique(c.name)) {
        emit categoryInvalid(InvalidReason::NameAlreadyExist);
        return;
    }

    if (!checkGroupExist(c.groupId)) {
        emit categoryInvalid(InvalidReason::GroupNotFound);
        return;
    }

    c.name = c.name.toLower();

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
    return !!m_repo->groups()->find(groupId);
}
