#include "transactionrepo.h"
#include <set>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <entities/transaction.h>
#include <repos/idatecolumnadapter.h>
#include <repos/transactionjsonmapper.h>

using namespace TransactionJsonMapper;

//void fillTransactions(Transactions & transactions) {

//    QFile f("/home/eugene/project/YourCounter/testdata/transactions.json");
//    f.open(QFile::ReadOnly | QFile::Text);
//    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
//    f.close();

//    QJsonObject obj = doc.object();

//    QJsonArray tarr = obj.value("transactions").toArray();
//    for (const auto & t : tarr)
//    {
//        transactions.push_back(fromJson(t.toObject()));
//    }

//}

TransactionRepo::TransactionRepo(IDateColumnAdapter * dateAdapter, ITransactionProvider * provider, QObject *parent)
    : ITransactionRepo(parent)
    , m_dateAdapter(dateAdapter)
    , m_provider(provider)
{
    Q_ASSERT(dateAdapter);

    connect(provider, &ITransactionProvider::transactionReady, this, [this](const Transactions & transactions ){
        std::set<QString> categoriesSet;
        m_transactions = std::move(transactions);
        for(const auto & t: m_transactions)
        {
            categoriesSet.insert(t.category);
        }
        m_categories.reserve(categoriesSet.size());
        for(const auto & c: categoriesSet)
        {
            m_categories.push_back(c);
        }
        //Do we really need that?
        std::sort(m_transactions.begin(), m_transactions.end(), [](const auto & a, const auto & b){
            return a.when < b.when;
        });
        emit dataChanged();
    });
    provider->loadTransactions();

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

const std::vector<QString> &TransactionRepo::getCategories()
{
    return m_categories;
}
