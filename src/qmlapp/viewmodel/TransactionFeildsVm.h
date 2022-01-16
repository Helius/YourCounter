#pragma once
#include <QObject>
#include <QRegularExpressionValidator>
#include <entities/Transaction.h>

class TransactionEditFeildsVm
    : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString category MEMBER m_category NOTIFY categoryChanged FINAL)
    Q_PROPERTY(QDateTime when MEMBER m_when NOTIFY whenChanged FINAL)
    Q_PROPERTY(QString who MEMBER m_who NOTIFY whoChanged FINAL)
    Q_PROPERTY(QString amount MEMBER m_amount NOTIFY amountChanged FINAL)
    Q_PROPERTY(QString comment MEMBER m_comment NOTIFY commentChanged FINAL)
    Q_PROPERTY(QRegularExpressionValidator* amountValidator MEMBER m_amountValidator CONSTANT FINAL)

public:
    //    TransactionEditFeildsVm(const Transaction& t, QObject* parent = nullptr);
    TransactionEditFeildsVm(QObject* parent = nullptr);
    //    Transaction buildTransaction();
    //    void setTransaction(const Transaction& t);

    void setCategory(const QString& category);
    void setWhen(const QDateTime& when);
    void setWho(const QString& who);
    void setAmount(const QString& amount);
    void setComment(const QString& comment);

signals:
    void categoryChanged();
    void whenChanged();
    void whoChanged();
    void amountChanged();
    void commentChanged();

private:
    QString m_category;
    QDateTime m_when;
    QString m_who;
    QString m_amount;
    QString m_comment;
    QRegularExpressionValidator* m_amountValidator = nullptr;
};
