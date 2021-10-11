#pragma once

#include <QString>

struct GroupRequest {
    GroupRequest() = delete;
    explicit GroupRequest(QString groupName)
    : name(std::move(groupName))
    {
        Q_ASSERT(!name.isEmpty());
    }
    QString name;
};