#include "transactionrepo.h"
#include <set>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <domain/entities/transaction.h>
#include <qmlapp/repos/idatecolumnadapter.h>
#include <qmlapp/repos/transactionjsonmapper.h>

using namespace TransactionJsonMapper;


TransactionRepo::TransactionRepo(std::shared_ptr<IDateColumnAdapter> dateAdapter, ITransactionProviderUnq provider)
    : m_dateAdapter(dateAdapter)
    , m_provider(std::move(provider))
{
    Q_ASSERT(m_dateAdapter);
    Q_ASSERT(m_provider);

    connect(m_dateAdapter.get(), &IDateColumnAdapter::scaleChanged, this, &TransactionRepo::dataChanged);

    connect(m_provider.get(), &ITransactionProvider::transactionReady, this, [this](const Transactions & transactions ){
        m_transactions = std::move(transactions);
        updateCategories();

        const auto [min, max] = std::minmax_element(m_transactions.cbegin(), m_transactions.cend(), []
                                             (const auto & a, const auto & b){
                                                        return a.amount < b.amount;
                                             });
        m_min = min->amount;
        m_max = max->amount;


//        std::sort(m_transactions.begin(), m_transactions.end(), [](const auto & a, const auto & b){
//            return a.when < b.when;
//        });

        emit dataChanged();
    });
    m_provider->loadTransactions();

}


bool TransactionRepo::hasColumnAmount(int column)
{
    for(const auto & t : m_transactions)
    {
        if(m_dateAdapter->isSame(column, t.when)) {
            return true;
        }
    }
    return false;
}

float TransactionRepo::columnAmountOverAll(int column)
{
    float amount = 0.0;
    for(const auto & t : m_transactions)
    {
        if(m_dateAdapter->isSame(column, t.when)) {
            amount += t.amount;
        }
    }
    return amount;
}

void TransactionRepo::addTransaction(Transaction t)
{
    m_transactions.push_back(std::move(t));
    updateCategories();
    emit dataChanged();
}

const Transactions &TransactionRepo::getTransactions()
{
    return m_transactions;
}

void TransactionRepo::updateCategories()
{
        m_categories.clear();
        std::set<QString> categoriesSet;
        for(const auto & t: m_transactions)
        {
            categoriesSet.insert(t.category);
        }
        m_categories.reserve(categoriesSet.size());
        for(const auto & c: categoriesSet)
        {
            m_categories.push_back(c);
        }
}

float TransactionRepo::calcAmount(int categoryInd, int column)
{
    std::vector<Transaction> daily;
    const auto & cat = m_categories[categoryInd];
    float amount = 0.0;
    for(const auto & t: m_transactions) {
        if((t.category == cat) && m_dateAdapter->isSame(column, t.when)) {
            daily.push_back(t);
            amount += t.amount;
        }
    }
    return amount;
}

const Categories &TransactionRepo::getCategories()
{
    return m_categories;
}