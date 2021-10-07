#include "transactionrepo.h"
#include <set>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <entities/transaction.h>
#include <repos/idatecolumnadapter.h>
#include "transactionjsonmapper.h"

using namespace TransactionJsonMapper;

TransactionRepo::TransactionRepo(FirebaseRtDbAPIUnq api)
        : m_api(std::move(api))
{
    Q_ASSERT(m_api);
    init();
}

void TransactionRepo::addTransaction(const TransactionRequest & t)
{
    m_api->addObject("/transactions", toJson(t));
}

void TransactionRepo::addCategory(const CategoryRequest & c)
{
    m_api->addObject("/categories", toJson(c));
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

void TransactionRepo::init() {

    m_transactions.clear();
    m_categories.clear();
    m_predictions.clear();

    auto loadTransactions = m_api->getObject("/transactions.json")
            .then(parseTransaction)
            .then([this](Transactions transactions){
                m_transactions.swap(transactions);
                emitIfReady();
            });

    auto loadCategory = m_api->getObject("/categories.json")
            .then(parseCategories)
            .then([this](Categories categories){
                m_categories.swap(categories);
                emitIfReady();
            });

    auto loadPredictions = m_api->getObject("/predictions.json")
            .then(parseTransaction)
            .then([this](Transactions transactions){
                m_predictions.swap(transactions);
                emitIfReady();
            });
}

void TransactionRepo::emitIfReady() {
    if (!m_transactions.empty() && !m_categories.empty() && !m_predictions.empty()) {
        emit dataChanged();
    }
}




