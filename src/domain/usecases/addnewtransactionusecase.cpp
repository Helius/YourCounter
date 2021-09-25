#include "addnewtransactionusecase.h"

AddNewTransactionUseCase::AddNewTransactionUseCase()
    : QObject()
{}

void AddNewTransactionUseCase::addTransaction(const Transaction &t)
{
    // check transaction valid
    if (abs(t.amount)>0.01)
    {
        if (!t.category.isEmpty())
        {
//            if(t.category)

        }
        else
        {
            emit transactionIvalid();
        }

    }
    else
    {
        emit transactionIvalid();
    }
}
