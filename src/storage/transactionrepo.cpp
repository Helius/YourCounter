#include "transactionrepo.h"
#include <set>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <entities/transaction.h>
#include "jsonMappers/transactionjsonmapper.h"
#include "jsonMappers/categoryMappers.h"
#include "jsonMappers/groupMappers.h"
#include <QTimer>

namespace {
    QLatin1String transactionsEndPoint("/transactions");
    QLatin1String categoriesEndPoint("/categories");
    QLatin1String groupsEndPoint("/groups");
    QLatin1String predictionsEndPoint("/predictions");

    template<typename T>
    QJsonObject updateObject(std::vector<T> container, const T & t)
    {
        using namespace TransactionJsonMapper;
        using namespace CategoryMappers;
        using namespace GroupMappers;

        QJsonObject patch;
        for(const auto & orig: container)
        {
            if (orig.id == t.id) {
                patch = diff(t, orig);
            }
        }
        return patch;
    }
}

using namespace TransactionJsonMapper;
using namespace CategoryMappers;
using namespace GroupMappers;

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
                }
                emit transactionsChanged();
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
                emit predictionsChanged();
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
                emit categoriesChanged();
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
                emit categoriesChanged();
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

void TransactionRepo::init()
{
    m_transactions.clear();
    m_categories.clear();
    m_predictions.clear();
    m_groups.clear();

    m_loadTransactions = m_api->getObject(transactionsEndPoint)
            .then(QtFuture::Launch::Async, parseTransactions)
            .then(this, [this, self=sharedFromThis()](Transactions transactions){
                Q_ASSERT(self);
                m_transactions.swap(transactions);
                emit transactionsChanged();
            });

    m_loadCategories = m_api->getObject(categoriesEndPoint)
            .then(QtFuture::Launch::Async, parseCategories)
            .then(this, [this, self=sharedFromThis()](Categories categories){
                Q_ASSERT(self);
                m_categories.swap(categories);
                emit categoriesChanged();
            });

    m_loadPredictions = m_api->getObject(predictionsEndPoint)
            .then(QtFuture::Launch::Async, parseTransactions)
            .then(this, [this, self=sharedFromThis()](Transactions transactions){
                Q_ASSERT(self);
                m_predictions.swap(transactions);
                emit predictionsChanged();
            });

    m_loadGroups = m_api->getObject(groupsEndPoint)
            .then(QtFuture::Launch::Async, parseGroups)
            .then(this, [this, self=sharedFromThis()](Groups groups){
                Q_ASSERT(self);
                m_groups.swap(groups);
                emit groupsChanged();
            });
}

void TransactionRepo::updateTransaction(const Transaction & t)
{
    QJsonObject patch = updateObject<Transaction>(m_transactions, t);
    Q_ASSERT(!patch.isEmpty());
    auto updateFuture = m_api->updateObjectByID(transactionsEndPoint, t.id, patch)
            .then(this, [this, self=sharedFromThis()](const QJsonObject &){
                emit transactionsChanged();
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

void TransactionRepo::updatePrediction(const Transaction & t) {
    QJsonObject patch = updateObject<Transaction>(m_predictions, t);
    Q_ASSERT(!patch.isEmpty());
    auto updateFuture = m_api->updateObjectByID(predictionsEndPoint, t.id, patch)
            .then(this, [this, self=sharedFromThis()](const QJsonObject &){
                emit predictionsChanged();
            });
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

