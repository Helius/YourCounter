#pragma once

#include <QObject>
#include <entities/Category.h>
#include <entities/Group.h>
#include <repos/IEntityRepo.h>

class AddNewCategoryUseCase
    : public QObject {

    Q_OBJECT

public:
    enum class InvalidReason : int {
        EmptyName = 0,
        GroupNotFound,
    };

    explicit AddNewCategoryUseCase(IEntityRepoPtr repo);

    void addCategory(Category g);

signals:
    void categoryInvalid(const InvalidReason& reason);
    void categoryAdded();

private:
    bool checkNameUnique(const QString& name);
    bool checkGroupExist(const QString& groupId);

private:
    IEntityRepoPtr m_repo;
};

using AddNewCategoryUseCaseUnq = std::unique_ptr<AddNewCategoryUseCase>;
