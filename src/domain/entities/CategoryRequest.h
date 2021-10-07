#pragma once

struct CategoryRequest {
    CategoryRequest() = delete;
    CategoryRequest(const QString & name)
            : name(name)
    {
        Q_ASSERT(!name.isEmpty());
    }
    QString name;
};

