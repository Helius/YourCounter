#pragma once
#include <QJsonObject>
#include <entities/Category.h>
#include <entities/CategoryRequest.h>

namespace CategoryMappers
{
    Categories parseCategories(const QJsonObject & transactions);
    Category categoryFromJson(const QString & id, const QJsonObject & object);
    QJsonObject diff(const Category & newT, const Category & oldT);
    QJsonObject toJson(const CategoryRequest & request);
    void patch(Category & cat, const QJsonObject & obj);
}