#pragma once

#include <QString>

struct Category {
    Category() = delete;
    Category(const QString name, const QString id)
    : name(name)
    , id(id)
    {};
    QString name;
    QString id;
    bool operator==(const Category & other) const {
        return id == other.id;
    }

    bool isValid() const {
        return !name.isEmpty();
    }
};

using Categories = std::vector<Category>;