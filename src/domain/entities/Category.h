#pragma once

#include <QString>

struct Category {
    Category() = delete;
    Category(const QString & name, const QString & id, const QString & groupId)
    : id(id)
    , name(name)
    , groupId(groupId)
    {};
    QString id;
    QString name;
    QString groupId;
    bool operator==(const Category & other) const {
        return id == other.id;
    }

    bool isValid() const {
        return !name.isEmpty() && !id.isEmpty();
    }
};

using Categories = std::vector<Category>;