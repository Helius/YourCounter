#include "GroupMappers.h"

namespace {
QLatin1String nameKey("name");
}

Group GroupMapper::fromJson(const QString& id, const QJsonObject& json)
{
    QString name = json[nameKey].toString();
    return Group::createFromValue(id, name);
}

QJsonObject GroupMapper::toJson(const Group& g)
{
    return { { nameKey, g.name } };
}

void GroupMapper::patch(Group& g, const QJsonObject& json)
{
    g.name = json.contains(nameKey) ? json[nameKey].toString() : g.name;
}

QJsonObject GroupMapper::diff(const Group& from, const Group& to)
{
    QJsonObject result;
    if (from.name != to.name) {
        result.insert(nameKey, to.name);
    }
    return result;
}
