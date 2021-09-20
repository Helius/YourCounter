#include "transactionproviderfromfile.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <repos/transactionjsonmapper.h>


TransactionProviderFromFile::TransactionProviderFromFile(const QString &filePath, QObject * parent)
    : ITransactionProvider(parent)
    , m_filePath(filePath)
{}


void TransactionProviderFromFile::loadTransactions()
{
    using namespace TransactionJsonMapper;
    Q_ASSERT(m_filePath.isEmpty());

    QFile f(m_filePath);
    f.open(QFile::ReadOnly | QFile::Text);
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();

    QJsonObject obj = doc.object();

    QJsonArray tarr = obj.value("transactions").toArray();
    for (const auto & t : tarr)
    {
        m_transactions.push_back(fromJson(t.toObject()));
    }
    emit transactionReady(m_transactions);
}
