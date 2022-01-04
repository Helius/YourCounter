#pragma once

#include <QObject>
#include <entities/Group.h>
#include <repos/IEntityRepo.h>

class AddNewGroupUseCase
    : public QObject {

    Q_OBJECT

public:
    enum class InvalidReason : int {
        EmptyName = 0,
        NameAlreadyExist
    };

    explicit AddNewGroupUseCase(IEntityRepoPtr repo);

    void addGroup(Group g);

signals:
    void groupInvalid(const InvalidReason& reason);
    void groupAdded();

private:
    bool checkNameUnique(const QString& name);

private:
    const IGroupRepoUnq& m_groups;
};

using AddNewGroupUseCaseUnq = std::unique_ptr<AddNewGroupUseCase>;
