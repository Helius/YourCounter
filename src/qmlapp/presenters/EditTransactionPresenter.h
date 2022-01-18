#pragma once

#include "../viewmodel/TransactionFeildsVm.h"
#include <QObject>
#include <usecases/EditTransactionUsecase.h>

class EditTransactionPresenter : public QObject {

    Q_OBJECT
    Q_PROPERTY(TransactionEditFeildsVm* vm MEMBER m_vm CONSTANT FINAL)

public:
    explicit EditTransactionPresenter(EditTransactionUsecaseUnq usecase, const QString& transactionId);

    Q_INVOKABLE void apply();

signals:
    void closePopup();

private:
    EditTransactionUsecaseUnq m_usecase;
    QString m_transactionId;
    QDateTime m_origTime;
    QString m_categoryId;
    TransactionEditFeildsVm* m_vm = nullptr;
};

using EditTransactionPresenterUnq = std::unique_ptr<EditTransactionPresenter>;

class EditTransactionBuilder {
public:
    EditTransactionBuilder(EditTransactionUsecaseUnq);
    EditTransactionPresenterUnq build(const QString& transactionId);

private:
    EditTransactionUsecaseUnq m_usecase;
};

using EditTransactionBuilderUnq = std::unique_ptr<EditTransactionBuilder>;