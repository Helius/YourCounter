#pragma once

#include <QJsonObject>
#include <entities/Group.h>
#include <entities/GroupRequest.h>

namespace GroupMappers
{
    Groups parseGroups(const QJsonObject & groups);
    Group groupFromJson(const QString & id, const QJsonObject & object);
    QJsonObject toJson(const GroupRequest &request);
    QJsonObject diff(const Group & newT, const Group & oldT);
    void patch(Group & g, const QJsonObject & obj);

}
