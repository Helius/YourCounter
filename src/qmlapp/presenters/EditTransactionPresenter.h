#pragma once

#include "../viewmodel/TransactionFeildsVm.h"
#include <QObject>
#include <usecases/EditTransactionUsecase.h>

class EditTransactionPresenter : public QObject {

    Q_OBJECT

public:
    explicit EditTransactionPresenter(EditTransactionUsecaseUnq usecase);

    Q_INVOKABLE void apply();
    void setTransactionId(const QString& transactionId);

signals:
    void closePopup();

private:
    EditTransactionUsecaseUnq m_usecase;
    TransactionEditFeildsVm* m_vm = nullptr;
    QString m_transactionId;
};

using EditTransactionPresenterUnq = std::unique_ptr<EditTransactionPresenter>;