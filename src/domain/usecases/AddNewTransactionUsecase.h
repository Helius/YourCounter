#pragma once

#include <QObject>
#include <entities/Transaction.h>
#include <repos/IEntityRepo.h>

class AddNewTransactionUseCase : public QObject
{
	Q_OBJECT
public:
	enum class InvalidReason : int
	{
		ZerroAmount = 0,
		EmptyCategory,
		CategoryNotFound,
		DateFarInThePast,
		DateFarInTheFuture,
		DateInvalid,
		EmptyWalletId
	};

	explicit AddNewTransactionUseCase(IEntityRepoPtr repo);

	void addTransaction(const Transaction & t);

signals:
	void transactionInvalid(const InvalidReason & r);
	bool isItNewCategory();
	void transactionAdded();

private:
	bool checkCategoryExist(const QString & category);

private:
	IEntityRepoPtr m_repo;
};

using AddNewTransactionUseCaseUnq = std::unique_ptr<AddNewTransactionUseCase>;
