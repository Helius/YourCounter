#pragma once

#include <QObject>
#include <repos/IEntityRepo.h>

class CurrentBalanceCalculateUsecase : public QObject {
    Q_OBJECT

public:
    explicit CurrentBalanceCalculateUsecase(IEntityRepoPtr repo);
    void calcBalance();

signals:
    void currentBalance(int64_t balance);

private:
    IEntityRepoPtr m_repo;
};

using CurrentBalanceCalculateUsecaseUnq = std::unique_ptr<CurrentBalanceCalculateUsecase>;
