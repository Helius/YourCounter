#include <utility>

#pragma once

struct CategoryRequest {
    CategoryRequest() = delete;
    explicit CategoryRequest(QString name, QString  groupId)
            : name(std::move(name))
            , groupId(std::move(groupId))
    {
        Q_ASSERT(!this->name.isEmpty());
    }
    QString name;
    QString groupId;
};

