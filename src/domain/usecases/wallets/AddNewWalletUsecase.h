#pragma once

#include <QObject>

#include <repos/IEntityRepo.h>

class AddNewWalletUseCase : public QObject {

    Q_OBJECT

public:
    explicit AddNewWalletUseCase(IEntityRepoPtr repo);

public:
    bool add(const QString& name, int64_t initAmount);

private:
    bool checkNameUnique(const QString& name);

private:
    const IWalletRepoUnq& m_repo;
};

using AddNewWalletUseCaseUnq = std::unique_ptr<AddNewWalletUseCase>;
