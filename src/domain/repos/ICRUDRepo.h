#pragma once
#include <QObject>
#include <QString>
#include <functional>

//class RepoObserver {

//public:
//    using ChangeListenerFun = std::function<void(UpdateMode mode, size_t startIndex, size_t size)>;
//    using ErrorListenerFun = std::function<void(QString error)>;

//public:
//    RepoObserver() = delete;
//    RepoObserver(ChangeListenerFun changeListener, ErrorListenerFun errorListener)
//        : changeListener(std::move(changeListener))
//        , errorListener(std::move(errorListener))
//    {
//    }

//    ChangeListenerFun changeListener;
//    ErrorListenerFun errorListener;
//};

class IRepoObserver : public QObject {

    Q_OBJECT

public:
    enum UpdateMode {
        Changed = 0,
        Inserted,
        Removed,
    };
    Q_ENUM(UpdateMode);
signals:
    void dataChanged(UpdateMode mode, size_t startIndex, size_t size);
    void onError(const QString& error);
};

//using RepoObserverWeak = std::weak_ptr<RepoObserver>;
//using RepoObserverPtr = std::shared_ptr<RepoObserver>;

template <typename Entity>
class ICRUDRepo : public IRepoObserver {
public:
    virtual void fetchAll() = 0;
    virtual void create(const Entity& t) = 0;
    virtual void remove(const Entity& t) = 0;
    virtual void update(const Entity& t) = 0;
    virtual bool fetched() = 0;
    virtual const std::vector<Entity>& data() = 0;
    //    virtual void addObserver(RepoObserverWeak observer) = 0;
    virtual ~ICRUDRepo() = default;
};
