#include "groupMappers.h"

namespace
{
    QLatin1String nameKey("name");
}

namespace GroupMappers
{
    Group groupFromJson(const QString & id, const QJsonObject & object) {
        QString name = object[nameKey].toString();
        return Group(id, name);
    }

    Groups parseGroups(const QJsonObject & groups) {
        Groups result;
        for(auto it = groups.constBegin(); it != groups.constEnd(); ++it) {
            result.push_back(groupFromJson(it.key(), it.value().toObject()));
        }
        return result;
    }

    QJsonObject toJson(const GroupRequest &request) {
        return {{nameKey, request.name}};
    }

    QJsonObject diff(const Group & newC, const Group & oldC)
    {
        QJsonObject result;
        if(newC.name != oldC.name) {
            result.insert(nameKey, newC.name);
        }
        return result;
    }

    void patch(Group &g, const QJsonObject &obj) {
        g.name = obj.contains(nameKey) ? obj[nameKey].toString() : g.name;
    }


}