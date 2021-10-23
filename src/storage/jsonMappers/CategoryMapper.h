#pragma once
#include <QJsonObject>
#include <entities/Category.h>
#include <entities/CategoryRequest.h>
#include "IJsonMapper.h"

class CategoryMapper : public IJsonMapper<Category>
{
public:
    Category fromJson(const QString &id, const QJsonObject &json) override;
    QJsonObject toJson(const Category &t) override;
    void patch(Category &t, const QJsonObject &json) override;
    QJsonObject diff(const Category &from, const Category &to) override;
};
