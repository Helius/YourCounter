#pragma once
#include <QObject>
#include <QRegularExpressionValidator>
#include <entities/Transaction.h>

class TransactionEditFeildsVm
    : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString categoryId MEMBER m_categoryId NOTIFY categoryIdChanged FINAL)
    Q_PROPERTY(QDateTime when MEMBER m_when NOTIFY whenChanged FINAL)
    Q_PROPERTY(QString who MEMBER m_who NOTIFY whoChanged FINAL)
    Q_PROPERTY(QString amount MEMBER m_amount NOTIFY amountChanged FINAL)
    Q_PROPERTY(QString coment MEMBER m_coment NOTIFY comentChanged FINAL)
    Q_PROPERTY(QRegularExpressionValidator* amountValidator MEMBER m_amountValidator CONSTANT FINAL)

public:
    TransactionEditFeildsVm(const Transaction& t, QObject* parent = nullptr);
    TransactionEditFeildsVm(QObject* parent = nullptr);
    Transaction buildTransaction();
    void setTransaction(const Transaction& t);

signals:
    void categoryIdChanged();
    void whenChanged();
    void whoChanged();
    void amountChanged();
    void comentChanged();

private:
    QString m_categoryId;
    QDateTime m_when;
    QString m_who;
    QString m_amount;
    QString m_coment;
    QRegularExpressionValidator* m_amountValidator = nullptr;
};
