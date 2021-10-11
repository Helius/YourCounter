#pragma once

#include <QString>
#include <utility>

struct Group {
    Group() = delete;
    Group(QString id, QString name)
    : id(std::move(id))
    , name(std::move(name))
    {
        Q_ASSERT(!this->name.isEmpty());
    }
    QString id;
    QString name;

    bool operator==(const Group & other) const {
        return id == other.id;
    }
};

using Groups = std::vector<Group>;