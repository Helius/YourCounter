#pragma once

#include <QDateTime>
#include <QObject>
#include <QRegularExpressionValidator>
#include <usecases/AddNewCategoryUsecase.h>


class AddCategoryPresenter : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString groupId MEMBER m_groupId NOTIFY groupIdChanged FINAL)

public:
    AddCategoryPresenter(AddNewCategoryUseCaseUnq usecase);

    Q_INVOKABLE void add();

signals:
    void nameChanged();
    void groupIdChanged();
    void closePopup();

private:
    AddNewCategoryUseCaseUnq m_usecase;
    QString m_name;
    QString m_groupId;
};

using AddCategoryPresenterUnq = std::unique_ptr<AddCategoryPresenter>;
