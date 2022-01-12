#pragma once
#include <QObject>
#include <entities/Transaction.h>
#include <QRegularExpressionValidator>

class TransactionFeildsVm
{
    Q_GADGET

    Q_PROPERTY(QString categoryId MEMBER m_categoryId NOTIFY categoryIdChanged FINAL)
    Q_PROPERTY(QDateTime when MEMBER m_when NOTIFY whenChanged FINAL)
    Q_PROPERTY(QString who MEMBER m_who NOTIFY whoChanged FINAL)
    Q_PROPERTY(QString amount MEMBER m_amount NOTIFY amountChanged FINAL)
    Q_PROPERTY(QString coment MEMBER m_coment NOTIFY comentChanged FINAL)

public:
    TransactionFeildsVm(const Transaction & t);
private:
    QString m_categoryId;
    QDateTime m_when;
    QString m_who;
    QString m_amount;
    QString m_coment;
    QRegularExpressionValidator* m_amountValidator = nullptr;
};
