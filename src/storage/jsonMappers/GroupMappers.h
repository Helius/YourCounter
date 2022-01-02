#pragma once

#include "IJsonMapper.h"
#include <QJsonObject>
#include <entities/Group.h>

class GroupMapper : public IJsonMapper<Group> {
    // IJsonMapper interface
public:
    Group fromJson(const QString& id, const QJsonObject& json);
    QJsonObject toJson(const Group& t);
    void patch(Group& g, const QJsonObject& json);
    QJsonObject diff(const Group& from, const Group& to);
};
