#pragma once

#include <QString>

struct Category {

    QString id;
    QString name;
    QString groupId;

    Category() = delete;
    static Category createRequest(const QString& name, const QString& groupId)
    {
        return Category(QString(), name, groupId);
    }
    static Category createFromValue(const QString& id, const QString& name, const QString& groupId)
    {
        return Category(id, name, groupId);
    }

    bool operator==(const Category& other) const { return id == other.id; }
    operator bool() const { return !id.isEmpty() && !name.isEmpty(); }

private:
    Category(
        const QString& id,
        const QString& name,
        const QString& groupId)
        : id(id)
        , name(name)
        , groupId(groupId) {};
};

using Categories = std::vector<Category>;
