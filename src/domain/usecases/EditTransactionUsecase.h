#pragma once

#include <repos/IEntityRepo.h>

class EditTransactionUsecase {

public:
    enum EditError {
        TransactionIdDiffer,
        CategoryNotFound,
        BadAmount,
        BadDate,
        BadOwner,
        Ok,
    };

    EditTransactionUsecase(IEntityRepoPtr repo);
    Transaction loadTransaction(const QString& transactionId);
    EditError applyChanges(const Transaction& t);

private:
    bool checkCategoryExist(const QString& categoryId);

private:
    IEntityRepoPtr m_repo;
    QString loadedTransactionId;
};

using EditTransactionUsecaseUnq = std::unique_ptr<EditTransactionUsecase>;
