#pragma once

#include <QObject>
#include <entities/transaction.h>
#include <repos/IEntityRepo.h>

class AddNewTransactionUseCase : public QObject {
    Q_OBJECT
public:
    enum class InvalidReason : int {
        ZerroAmount = 0,
        EmptyCategory,
    };

    explicit AddNewTransactionUseCase(IEntityRepoPtr repo);

    void addTransaction(const Transaction& t, bool allowNewCategory = false);

signals:
    void transactionInvalid(const InvalidReason& r);
    bool isItNewCategory();
    void transactionAdded();

private:
    bool checkCategoryExist(const Category& category);

private:
    IEntityRepoPtr m_repo;
};

using AddNewTransactionUseCaseUnq = std::unique_ptr<AddNewTransactionUseCase>;
