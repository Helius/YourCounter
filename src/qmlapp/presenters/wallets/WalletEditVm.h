#pragma once

#include <QObject>
#include <QRegularExpressionValidator>
#include <entities/Wallet.h>

class WalletEditVm
    : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString initAmount MEMBER m_initAmount NOTIFY initAmountChanged)
    Q_PROPERTY(QRegularExpressionValidator* amountValidator MEMBER m_amountValidator CONSTANT FINAL)

public:
    explicit WalletEditVm(QObject* parent = nullptr);
    WalletEditVm(const Wallet& w);

    QString getName() { return m_name; }
    QString getInitAmounnt() { return m_initAmount; }

signals:
    void nameChanged();
    void initAmountChanged();

private:
    QString m_name;
    QString m_initAmount;
    QRegularExpressionValidator* m_amountValidator = nullptr;
};
