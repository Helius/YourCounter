#pragma once

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <repos/IEntityRepo.h>

class CategoryListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles {
        Name,
        GroupName,
    };
    Q_ENUM(Roles);

    CategoryListModel(IEntityRepoPtr repo);

private:
    IEntityRepoPtr m_repo;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

using CategoryListModelUnq = std::unique_ptr<CategoryListModel>;

//class TransactionSortedListModel
//    : public QSortFilterProxyModel
//{
//    Q_OBJECT

//public:
//    TransactionSortedListModel(IEntityRepoPtr repo);

//    // QSortFilterProxyModel interface
//protected:
//    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

//private:
//    TransactionListModel * m_sourceModel;
//};

//using TransactionSortedListModelUnq = std::unique_ptr<TransactionSortedListModel>;
