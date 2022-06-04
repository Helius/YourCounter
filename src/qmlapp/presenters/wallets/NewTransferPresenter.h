#pragma once

#include <QObject>
#include <QRegularExpressionValidator>
#include <usecases/TransferUsecase.h>

class NewTransferPresenter : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString srcWallet READ srcWallet WRITE setSrcWallet NOTIFY srcWalletChanged FINAL)
    Q_PROPERTY(QString dstWallet READ dstWallet WRITE setdstWallet NOTIFY dstWalletChanged FINAL)
    Q_PROPERTY(QString amount READ amount WRITE setAmount NOTIFY amountChanged FINAL)
    Q_PROPERTY(QRegularExpressionValidator* amountValidator MEMBER m_amountValidator CONSTANT FINAL)

public:
    NewTransferPresenter(TransferUseCaseUnq usecase);

    const QString& dstWallet() const;
    void setdstWallet(const QString& newDstWallet);

    const QString& srcWallet() const;
    void setSrcWallet(const QString& newSrcWallet);

    const QString& amount() const;
    void setAmount(const QString& newAmount);

    Q_INVOKABLE bool add();

signals:
    void dstWalletChanged();

    void srcWalletChanged();

    void amountChanged();

private:
    TransferUseCaseUnq m_usecase;
    QString m_dstWallet;
    QString m_srcWallet;
    QString m_amount;
    QRegularExpressionValidator* m_amountValidator = nullptr;
};

using NewTransferPresenterUnq = std::unique_ptr<NewTransferPresenter>;