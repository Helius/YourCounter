#ifndef ADDTRANSACTIONBUTTONPRESENTER_H
#define ADDTRANSACTIONBUTTONPRESENTER_H

#include <QObject>
#include <repos/itransactionrepo.h>
#include <QDateTime>
#include <QRegularExpressionValidator>
#include <usecases/addnewtransactionusecase.h>

class AddTransactionButtonPresenter:
    public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString category MEMBER m_category NOTIFY categoryChanged FINAL)
    Q_PROPERTY(QDateTime when MEMBER m_when NOTIFY whenChanged FINAL)
    Q_PROPERTY(QString who MEMBER m_who NOTIFY whoChanged FINAL)
    Q_PROPERTY(QString amount MEMBER m_amount NOTIFY amountChanged FINAL)
    Q_PROPERTY(QString coment MEMBER m_coment NOTIFY comentChanged FINAL)

    Q_PROPERTY(QRegularExpressionValidator * amountValidator MEMBER m_amountValidator CONSTANT FINAL)

public:
    AddTransactionButtonPresenter(
        ITransactionRepoPtr repo,
        AddNewTransactionUseCaseUnq usecase);

    Q_INVOKABLE void add(bool allowNewCategory = false);

signals:
    void categoryChanged();
    void whenChanged();
    void whoChanged();
    void amountChanged();
    void comentChanged();
    void askAboutNewCategory();
    void closePopup();

private:
    ITransactionRepoPtr m_repo;
    AddNewTransactionUseCaseUnq m_usecase;
    QString m_category;
    QDateTime m_when;
    QString m_who;
    QString m_amount;
    QString m_coment;
    QRegularExpressionValidator * m_amountValidator;
};

using AddTransactionButtonPresenterUnq = std::unique_ptr<AddTransactionButtonPresenter>;

#endif // ADDTRANSACTIONBUTTONPRESENTER_H
