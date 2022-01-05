#pragma once

#include <QDateTime>
#include <QObject>
#include <QRegularExpressionValidator>
#include <usecases/AddNewGroupUsecase.h>

class AddGroupPresenter : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged FINAL)

public:
    AddGroupPresenter(AddNewGroupUseCaseUnq usecase);

    Q_INVOKABLE void add();

signals:
    void nameChanged();
    void closePopup();

private:
    AddNewGroupUseCaseUnq m_usecase;
    QString m_name;
};

using AddGroupPresenterUnq = std::unique_ptr<AddGroupPresenter>;
