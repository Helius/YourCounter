#include "transactionrepo.h"
#include <set>
#include <QString>
#include <entities/transaction.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace  {

QDateTime colToDateTime(int ind)
{
    return QDateTime(QDate(2021, 1, 1), QTime(0,0,0)).addDays(ind);
}

}

Transaction fromJson(const QJsonObject & obj)
{
    float amount = obj.value("amount").toDouble(0);
    QString category = obj.value("category").toString();
    if(category.isEmpty())
    {
        category = "Без категории";
    }
    QString comment = obj.value("comment").toString();
    QDateTime when = QDateTime::fromString(obj.value("when").toString(), Qt::DateFormat::ISODate);
    return Transaction(category, amount, when, comment);
}

QJsonObject toJson(const Transaction & transaction)
{
    return {
        {"amount", transaction.amount},
        {"category", transaction.category},
        {"comment", transaction.coment},
        {"when", transaction.when.toString(Qt::DateFormat::ISODate)}
    };
}

void fillTransactions(Transactions & transactions) {

    QFile f("/home/eugene/project/YourCounter/testdata/transactions.json");
    f.open(QFile::ReadOnly | QFile::Text);
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();

    QJsonObject obj = doc.object();

    QJsonArray tarr = obj.value("transactions").toArray();
    for (const auto & t : tarr)
    {
        transactions.push_back(fromJson(t.toObject()));
    }

    std::sort(transactions.begin(), transactions.end(), [](const auto & a, const auto & b){
        return a.when < b.when;
    });
}


TransactionRepo::TransactionRepo(QObject *parent)
    : ITransactionRepo(parent)
{
    fillTransactions(m_transactions);

    std::set<QString> categoriesSet;
    for(const auto & t: m_transactions)
    {
        categoriesSet.insert(t.category);
    }
    m_categories.reserve(categoriesSet.size());
    for(const auto & c: categoriesSet) {
        m_categories.push_back(c);
    }
}

bool TransactionRepo::hasDailyAmount(int dayNumber)
{
    for(const auto & t : m_transactions)
    {
        if(colToDateTime(dayNumber).daysTo(t.when) == 0) {
            return true;
        }
    }
    return false;
}

float TransactionRepo::dailyAmountOverAll(int dayNumber)
{
    float amount = 0.0;
    for(const auto & t : m_transactions)
    {
        if(colToDateTime(dayNumber).daysTo(t.when) == 0) {
            amount += t.amount;
        }
    }
    return amount;
}

float TransactionRepo::calcAmount(int categoryInd, int dayNumber)
{
    std::vector<Transaction> daily;
    const auto & cat = m_categories[categoryInd];
    float amount = 0.0;
    for(const auto & t: m_transactions) {
        if((t.category == cat) && (colToDateTime(dayNumber).daysTo(t.when) == 0)) {
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
