#pragma once
#include <QObject>
#include <QRegularExpressionValidator>
#include <entities/Transaction.h>

class TransactionEditFeildsVm
    : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString category READ category NOTIFY categoryChanged FINAL)
    Q_PROPERTY(QString categoryId READ categoryId WRITE setCategoryId NOTIFY categoryIdChanged FINAL)
    Q_PROPERTY(QDate when READ when WRITE setWhen NOTIFY whenChanged FINAL)
    Q_PROPERTY(QString who READ who WRITE setWho NOTIFY whoChanged FINAL)
    Q_PROPERTY(QString amount READ amount WRITE setAmount NOTIFY amountChanged FINAL)
    Q_PROPERTY(QString comment READ comment WRITE setComent NOTIFY commentChanged FINAL)
    Q_PROPERTY(QRegularExpressionValidator* amountValidator MEMBER m_amountValidator CONSTANT FINAL)

public:
    TransactionEditFeildsVm(QObject* parent = nullptr);
    TransactionEditFeildsVm(const QString& category,
        const QDate& when,
        const QString& who,
        const QString& amount,
        const QString& comment,
        QObject* parent = nullptr);

    QDate when() const;
    QString who() const;
    QString amount() const;
    QString comment() const;
    QString categoryId() const;
    QString category() const;

public slots:
    void setAmount(QString amount);
    void setComent(QString comment);
    void setWho(QString who);
    void setWhen(QDate when);
    void setCategoryId(QString categoryId);

signals:
    void categoryIdChanged();
    void categoryChanged();
    void whenChanged();
    void whoChanged();
    void amountChanged();
    void commentChanged();

private:
    QString m_category;
    QString m_categoryId;
    QDate m_when = QDate::currentDate();
    QString m_who;
    QString m_amount;
    QString m_comment;
    QRegularExpressionValidator* m_amountValidator = nullptr;
};
