#ifndef ADDNEWTRANSACTIONUSECASE_H
#define ADDNEWTRANSACTIONUSECASE_H

#include <QObject>
#include <domain/entities/transaction.h>
#include <domain/repos/itransactionrepo.h>


class AddNewTransactionUseCase : public QObject
{
    Q_OBJECT
public:

    enum class InvalidReason: int {
        BadAmount = 0,
        EmptyCategory,
    };

    explicit AddNewTransactionUseCase(ITransactionRepoPtr repo);

    void addTransaction(const Transaction & t);

signals:
    void transactionInvalid(const InvalidReason & r);
    bool isItNewCategory();
    void transactionAdded();

private:
    bool checkCategoryExist(const QString &category);

private:
    ITransactionRepoPtr m_repo;
};

using AddNewTransactionUseCaseUnq = std::unique_ptr<AddNewTransactionUseCase>;

#endif // ADDNEWTRANSACTIONUSECASE_H
