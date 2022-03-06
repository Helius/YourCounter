#include "CategoryListModel.h"

GroupListModel::GroupListModel(IEntityRepoPtr repo)
    : QAbstractListModel()
    , m_repo(repo)
{
    Q_ASSERT(m_repo);

    using UpdateMode = IRepoObserver::UpdateMode;

    connect(m_repo->groups().get(),
        &IRepoObserver::dataChanged,
        [this](UpdateMode mode, size_t startIndex, size_t size) {
            beginResetModel();
            qDebug() << "groups changed" << mode << startIndex << size;
            endResetModel();
        });
}

int GroupListModel::rowCount(const QModelIndex&) const
{
    return m_repo->groups()->data().size();
}

QVariant GroupListModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    if (static_cast<size_t>(row) >= m_repo->groups()->data().size()) {
        return QVariant();
    }

    switch (role) {
    case GroupName:
        return m_repo->groups()->data().at(row).name;
    case GroupId:
        return m_repo->groups()->data().at(row).id;
    }

    return QVariant();
}

QHash<int, QByteArray> GroupListModel::roleNames() const
{
    return {
        { Roles::GroupName, "groupName" },
        { Roles::GroupId, "groupId" }
    };
}

// ===

CategoryListModel::CategoryListModel(IEntityRepoPtr repo, QObject* parent)
    : QAbstractListModel(parent)
    , m_repo(repo)
{
    Q_ASSERT(repo);
    using UpdateMode = IRepoObserver::UpdateMode;
    connect(m_repo->categories().get(),
        &IRepoObserver::dataChanged,
        this,
        [this](UpdateMode mode, size_t startIndex, size_t size) {
            switch (mode) {
            case UpdateMode::Changed:
                break;
            case UpdateMode::Inserted:
                break;
            case UpdateMode::Removed:
                break;
            }
            beginResetModel();
            qDebug() << "categories changed" << mode << startIndex << size;
            endResetModel();
        });
}

int CategoryListModel::rowCount(const QModelIndex&) const
{
    return m_repo->categories()->data().size();
}

QVariant CategoryListModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    if (static_cast<size_t>(row) >= m_repo->categories()->data().size()) {
        return QVariant();
    }
    const auto& category = m_repo->categories()->data().at(row);
    const auto& groupOpt = m_repo->groups()->find(category.groupId);

    switch (role) {
    case Name:
        return category.name;
    case CategoryId:
        return category.id;
    case GroupId:
        return category.groupId;
    case GroupName:
        return groupOpt ? groupOpt->name : "???";
    }
    return QVariant();
}

QHash<int, QByteArray> CategoryListModel::roleNames() const
{
    return {
        { Roles::Name, "categoryName" },
        { Roles::CategoryId, "categoryId" },
        { Roles::GroupName, "groupName" },
    };
}

//===

CategorySortedListModel::CategorySortedListModel(IEntityRepoPtr m_repo)
    : QSortFilterProxyModel(nullptr)
    , m_sourceModel(new CategoryListModel(m_repo, this))
{
    setSourceModel(m_sourceModel);
}

void CategorySortedListModel::setGroupId(const QString& groupId)
{
    Q_ASSERT(!groupId.isEmpty());
    m_groupId = groupId;
}

bool CategorySortedListModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    return index.data(CategoryListModel::GroupId).toString() == m_groupId;
}

CategorySuggestModel::CategorySuggestModel(IEntityRepoPtr m_repo)
    : QSortFilterProxyModel(nullptr)
    , m_sourceModel(new CategoryListModel(m_repo, this))
{
    setSourceModel(m_sourceModel);
    setFilterRole(CategoryListModel::Roles::Name);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setDynamicSortFilter(true);
}

bool CategorySuggestModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    return (index.data(CategoryListModel::Roles::GroupName).toString() + index.data(CategoryListModel::Roles::Name).toString()).contains(filterRegularExpression());
}
