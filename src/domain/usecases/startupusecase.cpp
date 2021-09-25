#include "startupusecase.h"

StartupUseCase::StartupUseCase()
{

}

void StartupUseCase::start()
{
    QString dbUrl = emit getSavedDbUrl();

    if (dbUrl.isEmpty())
    {
        emit letUserChooseDb();
    }

    emit showDbData();
}
