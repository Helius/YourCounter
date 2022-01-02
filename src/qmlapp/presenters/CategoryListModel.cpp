#include "CategoryListModel.h"

CategoryListModel::CategoryListModel(IEntityRepoPtr repo)
    : QAbstractListModel()
    , m_repo(repo)
{
    Q_ASSERT(repo);

    // TODO: connect to changes of transactions, categories, groups

    //    connect(repo.get(), IEntityRepo::, this, [this](){
    //        emit layoutChanged();
    //    });
}

int CategoryListModel::rowCount(const QModelIndex&) const
{
    return m_repo->transactions()->data().size();
}

QVariant CategoryListModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    if (static_cast<size_t>(row) >= m_repo->categories()->data().size())
        return QVariant();
    auto category = m_repo->categories()->data().at(row);

    switch (role) {
    case Name:
        return category.name;
    case GroupName: {
        const auto groups = m_repo->groups()->data();
        const auto groupIt = std::find_if(groups.cbegin(), groups.cend(),
            [groupId = category.groupId](const auto& group) {
                return group.id == groupId;
            });
        return groupIt == groups.end() ? "NotFound" : groupIt->name;
    }
    }
    return QVariant();
}

QHash<int, QByteArray> CategoryListModel::roleNames() const
{
    return {
        { Roles::Name, "name" },
        { Roles::GroupName, "group" },
    };
}
