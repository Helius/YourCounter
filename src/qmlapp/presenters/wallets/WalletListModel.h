#pragma once

#include <QAbstractListModel>
#include <repos/IEntityRepo.h>

class WalletListModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QString error MEMBER m_error NOTIFY errorChanged FINAL)

public:
    enum Roles {
        Name = Qt::UserRole + 1,
        CurrentAmount,
        SourceCategoryName,
        Selected
    };

    explicit WalletListModel(IEntityRepoPtr repo);
    void clearSelection();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

signals:
    void errorChanged();

private:
    QString m_error;
    const IWalletRepoUnq& m_repo;
    int m_selectedInd = -1;
};

using WalletListModelUnq = std::unique_ptr<WalletListModel>;