#ifndef ADDNEWTRANSACTIONUSECASE_H
#define ADDNEWTRANSACTIONUSECASE_H

#include <QObject>
#include <domain/entities/transaction.h>


class AddNewTransactionUseCase : public QObject
{
    Q_OBJECT
public:
    explicit AddNewTransactionUseCase();

    void addTransaction(const Transaction & t);

signals:
    void transactionIvalid();
    void isItNewCategory();
    void transactionAdded();

};

using AddNewTransactionUseCaseUnq = std::unique_ptr<AddNewTransactionUseCase>;

#endif // ADDNEWTRANSACTIONUSECASE_H
