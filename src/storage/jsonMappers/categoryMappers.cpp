#include "categoryMappers.h"

namespace
{
    QLatin1String idKey("id");
    QLatin1String nameKey("name");
    QLatin1String groupIdKey("groupId");
}

namespace CategoryMappers
{

    Category categoryFromJson(const QString & id, const QJsonObject & object) {
        QString name = object[nameKey].toString();
        QString groupId = object[groupIdKey].toString();
        return Category(name, id, groupId);
    }

    Categories parseCategories(const QJsonObject &categories) {

        Categories result;
        for (auto it = categories.constBegin(); it != categories.constEnd(); ++it) {
            result.push_back(categoryFromJson(it.key(), it.value().toObject()));
        }
        return result;
    }

    QJsonObject diff(const Category & newC, const Category & oldC)
    {
        QJsonObject result;
        if(newC.name != oldC.name) {
            result.insert(nameKey, newC.name);
        }
        if(newC.groupId != oldC.groupId) {
            result.insert(groupIdKey, newC.groupId);
        }
        return result;
    }

    QJsonObject toJson(const CategoryRequest &request) {
        return {{nameKey, request.name}, {groupIdKey, request.groupId }};
    }

    void patch(Category & cat, const QJsonObject & obj)
    {
        cat.name = obj.contains(nameKey) ? obj[nameKey].toString() : cat.name;
        cat.groupId = obj.contains(groupIdKey) ? obj[groupIdKey].toString() : cat.groupId;
    }

}