#ifndef ISETTINGSREPOSITORY_H
#define ISETTINGSREPOSITORY_H

#include <QObject>

class ISettingsRepository : public QObject
{
    Q_OBJECT

public:
    virtual QString getSavedDbUrl() = 0;


    ~ISettingsRepository() = default;
    using QObject::QObject;

};

#endif // ISETTINGSREPOSITORY_H
