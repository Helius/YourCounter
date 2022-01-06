#pragma once

#include <QObject>
#include <usecases/CurrentBalanceCalculateUsecase.h>

class CurentBalancePresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentBalance READ currentBalance NOTIFY currentBalanceChanged FINAL)


public:
    explicit CurentBalancePresenter(CurrentBalanceCalculateUsecaseUnq usecase);

    QString currentBalance() const;

signals:
    void currentBalanceChanged();

private:
    void updateBalance(int64_t balance);

private:
    QString m_currentBalance;
    CurrentBalanceCalculateUsecaseUnq m_usecase;
};

using CurentBalancePresenterUnq = std::unique_ptr<CurentBalancePresenter>;