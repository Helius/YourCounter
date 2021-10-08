#pragma once

#include <QString>
#include <utility>

struct Group {
    Group() = delete;
    Group(QString  id, QString name)
    : id(std::move(id))
    , name(std::move(name))
    {
        Q_ASSERT(!name.isEmpty());
    }
    QString id;
    QString name;
};

using Groups = std::vector<Group>;