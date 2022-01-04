#include "AddNewGroupUsecase.h"

AddNewGroupUseCase::AddNewGroupUseCase(IEntityRepoPtr repo)
    : QObject()
    , m_groups(repo->groups())
{
    Q_ASSERT(m_groups);
}

void AddNewGroupUseCase::addGroup(Group g)
{
    Q_ASSERT(g.id.isEmpty());

    if (g.name.isEmpty()) {
        emit groupInvalid(InvalidReason::EmptyName);
        return;
    }

    if (!checkNameUnique(g.name)) {
        emit groupInvalid(InvalidReason::NameAlreadyExist);
        return;
    }

    g.name = g.name.toLower();

    //TODO: get future and wait
    m_groups->create(g);
    emit groupAdded();
}

bool AddNewGroupUseCase::checkNameUnique(const QString& name)
{
    const auto& groups = m_groups->data();
    const auto& result = std::find_if(groups.cbegin(), groups.cend(), [name](const auto& g) {
        return g.name.toLower() == name.toLower();
    });
    return result == groups.cend();
}
