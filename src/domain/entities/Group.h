#pragma once

#include <QString>
#include <utility>

struct Group {
    QString id;
    QString name;

    Group() = delete;
    Group(QString id, const QString& name)
        : id(std::move(id))
        , name(name.toLower())
    {
        Q_ASSERT(!this->name.isEmpty());
    }

    bool operator==(const Group& other) const { return id == other.id; }
    operator bool() const { return !id.isEmpty() && !name.isEmpty(); }
};

using Groups = std::vector<Group>;
