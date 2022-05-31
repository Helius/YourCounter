#pragma once

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <repos/IEntityRepo.h>

class GroupListModel
    : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        GroupName = Qt::UserRole + 1,
        GroupId
    };

    GroupListModel(IEntityRepoPtr repo);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    IEntityRepoPtr m_repo;
};

using GroupListModelUnq = std::unique_ptr<GroupListModel>;

class CategoryListModel
    : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles {
        CategoryId = Qt::UserRole + 1,
        Name,
        GroupId,
        GroupName,
    };
    Q_ENUM(Roles);

    CategoryListModel(IEntityRepoPtr repo, QObject* parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    IEntityRepoPtr m_repo;
};
//using CategoryListModelUnq = std::unique_ptr<CategoryListModel>;

class CategorySortedListModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    CategorySortedListModel(IEntityRepoPtr m_repo);
    void setGroupId(const QString& groupId);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;

private:
    CategoryListModel* m_sourceModel;
    QString m_groupId;
};

using CategorySortedListModelUnq = std::unique_ptr<CategorySortedListModel>;

// ====

class CategorySuggestModel : public QSortFilterProxyModel {

    Q_OBJECT

public:
    CategorySuggestModel(IEntityRepoPtr m_repo);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;

private:
    CategoryListModel* m_sourceModel;
};
using CategorySuggestModelUnq = std::unique_ptr<CategorySuggestModel>;