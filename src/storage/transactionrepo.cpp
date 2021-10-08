#include "transactionrepo.h"
#include <set>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <entities/transaction.h>
#include "transactionjsonmapper.h"

namespace {
    QLatin1String transactionsEndPoint("/transactions");
    QLatin1String categoriesEndPoint("/categories");
    QLatin1String groupsEndPoint("/groups");
    QLatin1String predictionsEndPoint("/predictions");
}

using namespace TransactionJsonMapper;

TransactionRepo::TransactionRepo(FirebaseRtDbAPIUnq api)
        : m_api(std::move(api))
{
    Q_ASSERT(m_api);
    init();
}

void TransactionRepo::addTransaction(const TransactionRequest &tr) {
    m_api->addObject(transactionsEndPoint, toJson(tr))
            .then(this, [this](QJsonObject obj) {
                auto t = parseTransactions(obj);
                Q_ASSERT(t.size() == 1);
                if (!t.empty()) {
                    m_transactions.push_back(t.front());
                }
                emit transactionsChanged();
            });
}

void TransactionRepo::addPrediction(const TransactionRequest &tr) {
    m_api->addObject(predictionsEndPoint, toJson(tr))
            .then(this, [this](QJsonObject obj) {
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
            .then(this, [this](QJsonObject obj) {
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
    .then(this, [this](QJsonObject obj) {
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

const Transactions &TransactionRepo::getPredictions() {
    return m_predictions;
}

const Groups &TransactionRepo::getGroups() {
    return m_groups;
}

void TransactionRepo::init() {

    m_transactions.clear();
    m_categories.clear();
    m_predictions.clear();
    m_groups.clear();

    m_loadTransactions = m_api->getObject(transactionsEndPoint)
            .then(QtFuture::Launch::Async, parseTransactions)
            .then(this, [this](Transactions transactions){
                m_transactions.swap(transactions);
                emit transactionsChanged();
            });

    m_loadCategories = m_api->getObject(categoriesEndPoint)
            .then(QtFuture::Launch::Async, parseCategories)
            .then(this, [this](Categories categories){
                m_categories.swap(categories);
                emit categoriesChanged();
            });

    m_loadPredictions = m_api->getObject(predictionsEndPoint)
            .then(QtFuture::Launch::Async, parseTransactions)
            .then(this, [this](Transactions transactions){
                m_predictions.swap(transactions);
                emit predictionsChanged();
            });

    m_loadGroups = m_api->getObject(groupsEndPoint)
            .then(QtFuture::Launch::Async, parseGroups)
            .then(this, [this](Groups groups){
                m_groups.swap(groups);
                groupsChanged();
            });
}

void TransactionRepo::setTransactionCategory(const Transaction &t, const Category &c) {
    auto updateFuture = m_api->updateObjectByID(
            transactionsEndPoint, t.id, {{"category", c.id}});
}

void TransactionRepo::setCategoryGroup(const Category &c, const Group &g) {
    auto updateFuture = m_api->updateObjectByID(
            categoriesEndPoint, c.id, {{"group", g.id}});
}





