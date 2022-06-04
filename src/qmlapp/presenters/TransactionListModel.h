#ifndef TRANSACTIONLISTMODEL_H
#define TRANSACTIONLISTMODEL_H

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <repos/IEntityRepo.h>
#include <set>

class TransactionListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles {
        Id = Qt::UserRole + 1,
        CategoryName,
        CategoryId,
        Amount,
        Date,
        Who,
        RawDate,
        Comment,
        Selected,
        TotalBy,
        AmountRaw,
        WalletId,
        WalletName,
    };
    Q_ENUM(Roles);

    TransactionListModel(IEntityRepoPtr repo, QObject* parent);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QString selectedAmountStr();

signals:
    void selectedAmountChanged();

private:
    QString getTransactionName(const Transaction& t) const;
    QString getWalletName(const Transaction &t) const;
    QString formatDate(const QDateTime& dateTime) const;
    void updateSelectedAmount();

private:
    IEntityRepoPtr m_repo;
    std::set<int> m_selectedItems;
    int64_t m_selectedAmount = 0;
};

class TransactionSortedListModel
    : public QSortFilterProxyModel {
    Q_OBJECT
    Q_PROPERTY(QString selectedAmount READ selectedAmount NOTIFY selectedAmountChanged FINAL)
    Q_PROPERTY(QString currentWalletId READ currentWalletId WRITE setCurrentWalletId NOTIFY currentWalletIdChanged)

public:
    TransactionSortedListModel(IEntityRepoPtr repo);
    const QString selectedAmount() const;
    QString currentWalletId() const
    {
        return m_currentWalletId;
    }
    void setCurrentWalletId(const QString& walletId);

signals:
    void selectedAmountChanged();
    void currentWalletIdChanged();

protected:
    // QSortFilterProxyModel interface
    bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
    // QAbstractItemModel interface
    QVariant data(const QModelIndex& index, int role) const override;
    // QSortFilterProxyModel interface
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;

private:
    int64_t proxyData(const QModelIndex& index, int role) const;

private:
    TransactionListModel* m_sourceModel;
    mutable std::map<int, int64_t> m_cachedTotalBy;
    QString m_currentWalletId;
};

using TransactionSortedListModelUnq = std::unique_ptr<TransactionSortedListModel>;

#endif // TRANSACTIONLISTMODEL_H
