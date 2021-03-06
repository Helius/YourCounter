#include "CategoryMapper.h"

namespace {

QLatin1String nameKey("name");
QLatin1String groupIdKey("groupId");

} // namespace

Category CategoryMapper::fromJson(const QString& id, const QJsonObject& json)
{
    QString name = json[nameKey].toString();
    QString groupId = json[groupIdKey].toString();
    return Category::createFromValue(id, name, groupId);
}

QJsonObject CategoryMapper::toJson(const Category& t)
{
    return { { nameKey, t.name }, { groupIdKey, t.groupId } };
}

void CategoryMapper::patch(Category& cat, const QJsonObject& json)
{
    cat.name = json.contains(nameKey) ? json[nameKey].toString() : cat.name;
    cat.groupId = json.contains(groupIdKey) ? json[groupIdKey].toString() : cat.groupId;
}

QJsonObject CategoryMapper::diff(const Category& from, const Category& to)
{
    QJsonObject result;
    if (to.name != from.name) {
        result.insert(nameKey, to.name);
    }
    if (to.groupId != from.groupId) {
        result.insert(groupIdKey, to.groupId);
    }
    return result;
}