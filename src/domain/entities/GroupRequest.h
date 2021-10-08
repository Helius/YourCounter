#pragma once

#include <QString>

struct GroupRequest {
    GroupRequest() = delete;
    explicit GroupRequest(QString name)
    : name(std::move(name))
    {
        Q_ASSERT(!name.isEmpty());
    }
    QString name;
};