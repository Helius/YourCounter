#pragma once

#include <QObject>

#include <repos/IEntityRepo.h>

class AddNewWalletUseCase : public QObject {

    Q_OBJECT

public:
    explicit AddNewWalletUseCase(IEntityRepoPtr repo);

public:
    void add(const QString& name, const CategoryId srcId);

signals:
    void error(QString error);

private:
    bool checkNameUnique(const QString& name);

private:
    const IWalletRepoUnq& m_repo;
};

using AddNewWalletUseCaseUnq = std::unique_ptr<AddNewWalletUseCase>;
