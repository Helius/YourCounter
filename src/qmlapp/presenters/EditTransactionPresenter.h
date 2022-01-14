#pragma once

#include "../viewmodel/TransactionFeildsVm.h"
#include <QObject>
#include <usecases/EditTransactionUsecase.h>

class EditTransactionPresenter : public QObject {

    Q_OBJECT
    Q_PROPERTY(TransactionEditFeildsVm* vm MEMBER m_vm CONSTANT FINAL)
    Q_PROPERTY(QString transactionId READ transactionId WRITE setTransactionId NOTIFY transactionIdChanged)

public:
    explicit EditTransactionPresenter(EditTransactionUsecaseUnq usecase);

    Q_INVOKABLE void apply();
    void setTransactionId(const QString& transactionId);
    QString transactionId() { return m_transactionId; }

signals:
    void closePopup();
    void transactionIdChanged();

private:
    EditTransactionUsecaseUnq m_usecase;
    TransactionEditFeildsVm* m_vm = nullptr;
    QString m_transactionId;
};

using EditTransactionPresenterUnq = std::unique_ptr<EditTransactionPresenter>;