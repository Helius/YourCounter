#pragma once

#include "WalletEditVm.h"
#include <QObject>
#include <usecases/wallets/AddNewWalletUsecase.h>

class AddNewWalletPresenter : public QObject {

    Q_OBJECT
    Q_PROPERTY(WalletEditVm* vm MEMBER m_vm CONSTANT FINAL)

public:
    explicit AddNewWalletPresenter(AddNewWalletUseCaseUnq);

    Q_INVOKABLE void add();

signals:
    void close();

private:
    AddNewWalletUseCaseUnq m_usecase;
    WalletEditVm* m_vm = nullptr;
};

using AddNewWalletPresenterUnq = std::unique_ptr<AddNewWalletPresenter>;