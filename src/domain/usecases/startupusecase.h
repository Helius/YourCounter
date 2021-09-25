#ifndef STARTUPUSECASE_H
#define STARTUPUSECASE_H

#include <QObject>

class StartupUseCase
    : public QObject
{
    Q_OBJECT

public:
    StartupUseCase();

public slots:
    void start();

signals:
    QString getSavedDbUrl();

    void letUserChooseDb();
    void showDbData();
};

#endif // STARTUPUSECASE_H
