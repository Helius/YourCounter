#pragma once

#include <QString>

struct Category {
    Category() = delete;
    Category(QString name, QString id)
    : name(std::move(name))
    , id(std::move(id))
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