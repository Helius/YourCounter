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
        Id,
        CategoryName,
        Amount,
        Date,
        Who,
        RawDate,
        Comment,
        Selected,
        TotalBy,
        AmountRaw,
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
    QString getCategoryName(const QString& id) const;
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

public:
    TransactionSortedListModel(IEntityRepoPtr repo);
    const QString selectedAmount() const;

signals:
    void selectedAmountChanged();

    // QSortFilterProxyModel interface
protected:
    bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex& index, int role) const override;

private:
    TransactionListModel* m_sourceModel;

private:
    int64_t proxyData(const QModelIndex& index, int role) const;

private:
    mutable std::map<int, int64_t> m_cachedTotalBy;
};

using TransactionSortedListModelUnq = std::unique_ptr<TransactionSortedListModel>;

#endif // TRANSACTIONLISTMODEL_H
