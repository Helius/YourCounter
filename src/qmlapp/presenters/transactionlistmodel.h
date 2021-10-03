#ifndef TRANSACTIONLISTMODEL_H
#define TRANSACTIONLISTMODEL_H

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <domain/repos/itransactionrepo.h>

class TransactionListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        Category,
        Amount,
        Date,
        Who,
        RawDate
    };
    Q_ENUM(Roles);

    TransactionListModel(ITransactionRepoPtr repo, QObject *parent = nullptr);
private:
    ITransactionRepoPtr m_repo;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};





class TransactionSortedListModel
    : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TransactionSortedListModel(ITransactionRepoPtr repo);

    // QSortFilterProxyModel interface
protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

private:
    TransactionListModel * m_sourceModel;
};


using TransactionSortedListModelUnq = std::unique_ptr<TransactionSortedListModel>;

#endif // TRANSACTIONLISTMODEL_H
