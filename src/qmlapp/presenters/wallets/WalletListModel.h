#pragma once

#include <QAbstractListModel>
#include <repos/IEntityRepo.h>
#include <repos/IWalletBallanceProvider.h>

class WalletListModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QString selectedWalletId READ selectedWalletId NOTIFY selectedWalletIdChanged FINAL)
    // Q_PROPERTY(QString defaultWalletTotal READ defaultWalletTotal NOTIFY defaultWalletTotalChanged FINAL)

public:
    enum Roles {
        Name = Qt::UserRole + 1,
        CurrentAmount,
        Selected
    };

    explicit WalletListModel(IWalletBallanceProviderPtr ballanceProvider);
    QString selectedWalletId();

    Q_INVOKABLE void clearSelection();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    // QString defaultWalletTotal() const;

signals:
    void selectedWalletIdChanged();
    void defaultWalletTotalChanged();

private:
    const IWalletBallanceProviderPtr m_ballanceProvider;
    int m_selectedInd = -1;
};

using WalletListModelUnq = std::unique_ptr<WalletListModel>;
