#pragma once

#include "../viewmodel/TransactionFeildsVm.h"
#include <QObject>
#include <usecases/AddNewTransactionUsecase.h>

class AddTransactionPresenter : public QObject {
    Q_OBJECT

    Q_PROPERTY(TransactionEditFeildsVm* vm MEMBER m_vm CONSTANT FINAL)

public:
    AddTransactionPresenter(AddNewTransactionUseCaseUnq usecase);

    Q_INVOKABLE void apply();
	Q_INVOKABLE void initWithData(const QString & text);

signals:
    void closePopup();

private:
    AddNewTransactionUseCaseUnq m_usecase;
    TransactionEditFeildsVm* m_vm = nullptr;
};

using AddTransactionPresenterUnq = std::unique_ptr<AddTransactionPresenter>;
