#include "transactionproviderfromfile.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <qmlapp/repos/transactionjsonmapper.h>


TransactionProviderFromFile::TransactionProviderFromFile(const QString &filePath)
    : m_filePath(filePath)
{
    qDebug() << "helius: transactionprovider CTOR";
}

TransactionProviderFromFile::~TransactionProviderFromFile()
{
    qDebug() << "helius: transactionprovider ~DTOR";
}


void TransactionProviderFromFile::loadTransactions()
{
    using namespace TransactionJsonMapper;
    Q_ASSERT(!m_filePath.isEmpty());

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
