#pragma once

#include <QObject>

class IRepoObserver : public QObject {
    Q_OBJECT
public:
    enum UpdateMode {
        Changed = 0,
        Inserted,
        Removed,
    };

signals:
    void dataChanged(UpdateMode mode, size_t startIndex, size_t size);
    void onError(const QString& msg);
};

template <typename Entity>
class ICRUDRepo : public IRepoObserver {
public:
    virtual void fetchAll() = 0;
    virtual void create(const Entity& t) = 0;
    virtual void remove(const Entity& t) = 0;
    virtual void update(const Entity& t) = 0;
    virtual bool fetched() = 0;
    virtual const std::vector<Entity>& data() = 0;
};
