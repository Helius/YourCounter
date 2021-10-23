#include "transactionrepo.h"
#include <set>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <entities/transaction.h>
#include "jsonMappers/TransactionMapper.h"
#include "jsonMappers/CategoryMapper.h"
#include "jsonMappers/GroupMappers.h"
#include <QTimer>

namespace {
//    QLatin1String transactionsEndPoint("/transactions");
//    QLatin1String categoriesEndPoint("/categories");
//    QLatin1String groupsEndPoint("/groups");
//    QLatin1String predictionsEndPoint("/predictions");

//    template<typename T>
//    QJsonObject updateObject(std::vector<T> container, const T & t)
//    {
//        using namespace TransactionJsonMapper;
//        using namespace CategoryMappers;
//
//        QJsonObject patch;
//        for(const auto & orig: container)
//        {
//            if (orig.id == t.id) {
//                patch = diff(t, orig);
//            }
//        }
//        return patch;
//    }
//
//    template<typename T>
//    size_t idToIndex(const T & t, const QString & id)
//    {
//        return std::distance(find_if(t.begin(), t.end(), [id](const auto & v){
//            return id == v.id;
//        }), t.cbegin());
//    }

}
/*
using namespace TransactionJsonMapper;
using namespace CategoryMappers;

TransactionRepo::TransactionRepo(IFirebaseRtDbAPIUnq api)
        : ITransactionRepo()
        , m_api(std::move(api))
{
    Q_ASSERT(m_api);
}

void TransactionRepo::addTransaction(const TransactionRequest &tr)
{
    m_api->addObject(transactionsEndPoint, toJson(tr))
            .then(this, [this, self=sharedFromThis()](const QJsonObject& obj) {
                Q_ASSERT(self);
                auto t = parseTransactions(obj);
                Q_ASSERT(t.size() == 1);
                if (!t.empty()) {
                    m_transactions.push_back(t.front());
                    emit transactionsChanged(m_transactions.size()-1);
                }
            });
}

void TransactionRepo::addPrediction(const TransactionRequest &tr)
{
    m_api->addObject(predictionsEndPoint, toJson(tr))
            .then(this, [this, self=sharedFromThis()](const QJsonObject& obj) {
                Q_ASSERT(self);
                auto t = parseTransactions(obj);
                Q_ASSERT(t.size() == 1);
                if (!t.empty()) {
                    m_predictions.push_back(t.front());
                }
                emit predictionsChanged(m_predictions.size()-1);
            });
}

void TransactionRepo::addCategory(const CategoryRequest & cr)
{
    m_api->addObject(categoriesEndPoint, toJson(cr))
            .then(this, [this, self=sharedFromThis()](const QJsonObject& obj) {
                Q_ASSERT(self);
                auto t = parseCategories(obj);
                Q_ASSERT(t.size() == 1);
                if (!t.empty()) {
                    m_categories.push_back(t.front());
                }
                emit categoriesChanged(m_categories.size()-1);
            });
}

void TransactionRepo::addGroup(const GroupRequest &gr) {
    m_api->addObject(groupsEndPoint, toJson(gr))
            .then(this, [this, self = sharedFromThis()](const QJsonObject &obj) {
                Q_ASSERT(self);
                auto t = parseGroups(obj);
                Q_ASSERT(t.size() == 1);
                if (!t.empty()) {
                    m_groups.push_back(t.front());
                }
                emit categoriesChanged(m_groups.size()-1);
            });
}

const Transactions &TransactionRepo::getTransactions()
{
    return m_transactions;
}

const Categories &TransactionRepo::getCategories()
{
    return m_categories;
}

const Transactions &TransactionRepo::getPredictions()
{
    return m_predictions;
}

const Groups &TransactionRepo::getGroups()
{
    return m_groups;
}

void TransactionRepo::init() {
    m_transactions.clear();
    m_categories.clear();
    m_predictions.clear();
    m_groups.clear();

    m_loadTransactions = m_api->getObject(transactionsEndPoint)
            .then(QtFuture::Launch::Async, parseTransactions)
            .then(this, [this, self=sharedFromThis()](Transactions transactions){
                Q_ASSERT(self);
                m_transactions.swap(transactions);
                emit transactionsChanged(-1);
            });

    m_loadCategories = m_api->getObject(categoriesEndPoint)
            .then(QtFuture::Launch::Async, parseCategories)
            .then(this, [this, self=sharedFromThis()](Categories categories){
                Q_ASSERT(self);
                m_categories.swap(categories);
                emit categoriesChanged(-1);
            });

    m_loadPredictions = m_api->getObject(predictionsEndPoint)
            .then(QtFuture::Launch::Async, parseTransactions)
            .then(this, [this, self=sharedFromThis()](Transactions transactions){
                Q_ASSERT(self);
                m_predictions.swap(transactions);
                emit predictionsChanged(-1);
            });

    m_loadGroups = m_api->getObject(groupsEndPoint)
            .then(QtFuture::Launch::Async, parseGroups)
            .then(this, [this, self=sharedFromThis()](Groups groups){
                Q_ASSERT(self);
                m_groups.swap(groups);
                emit groupsChanged(-1);
            });
}

void TransactionRepo::updateTransaction(const Transaction & t) {
    QJsonObject patch = updateObject<Transaction>(m_transactions, t);
    Q_ASSERT(!patch.isEmpty());
    auto updateFuture = m_api->updateObjectByID(transactionsEndPoint, t.id, patch)
            .then(this, [this, self=sharedFromThis(), id = t.id](const QJsonObject & o) {
                Transaction ut = transactionFromJson(id, o);
                size_t ind = idToIndex(m_transactions, id);
                if (ind < m_transactions.size()) {
                    m_transactions[ind] = ut;
                    emit transactionsChanged(ind);
                } else {
                    Q_ASSERT(false && "can't find updated transactions by id");
                }
            });
}

void TransactionRepo::updatePrediction(const Transaction & t) {
    QJsonObject patch = updateObject<Transaction>(m_predictions, t);
    Q_ASSERT(!patch.isEmpty());
    auto updateFuture = m_api->updateObjectByID(predictionsEndPoint, t.id, patch)
            .then(this, [this, self=sharedFromThis()](const QJsonObject &){
                emit predictionsChanged(123);
            });
}

void TransactionRepo::updateGroup(const Group & g) {
    QJsonObject patch = updateObject<Group>(m_groups, g);
    auto updateFuture = m_api->updateObjectByID(
            groupsEndPoint, g.id, patch);
}

void TransactionRepo::updateCategory(const Category & c) {
    QJsonObject patch = updateObject<Category>(m_categories, c);
    auto updateFuture = m_api->updateObjectByID(
            categoriesEndPoint, c.id, patch);
}

TransactionRepo::~TransactionRepo() {
    m_loadPredictions.cancel();
    m_loadTransactions.cancel();
    m_loadGroups.cancel();
    m_loadCategories.cancel();
}

QSharedPointer<ITransactionRepo> TransactionRepo::getInstance(IFirebaseRtDbAPIUnq api) {
    QSharedPointer<TransactionRepo> repo( new TransactionRepo(std::move(api)));
    return repo->gePtr();
}

QSharedPointer<ITransactionRepo> TransactionRepo::gePtr() {
    return sharedFromThis();
}

*/
