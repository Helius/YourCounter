#pragma once

#include <QString>

struct Category {

    QString id;
    QString name;
    QString groupId;

    Category() = delete;
    Category(const QString& name,
        const QString& id,
        const QString& groupId)
        : id(id)
        , name(name)
        , groupId(groupId) {};

    bool operator==(const Category& other) const { return id == other.id; }
    operator bool() const { return !id.isEmpty() && !name.isEmpty(); }
};

using Categories = std::vector<Category>;
