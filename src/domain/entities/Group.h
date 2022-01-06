#pragma once

#include <QString>

struct Group {
    QString id;
    QString name;

    Group() = delete;

    static Group createFromValue(QString id, const QString& name)
    {
        return Group(id, name);
    }
    static Group createRequest(const QString& name)
    {
        return Group(name);
    }

    bool operator==(const Group& other) const { return id == other.id; }
    operator bool() const { return !id.isEmpty() && !name.isEmpty(); }

private:
    Group(QString id, const QString& name)
        : id(std::move(id))
        , name(name.toLower())
    {
        Q_ASSERT(!this->name.isEmpty());
    }

    Group(const QString& name)
        : name(name.toLower())
    {
        Q_ASSERT(!this->name.isEmpty());
    }
};

using Groups = std::vector<Group>;
