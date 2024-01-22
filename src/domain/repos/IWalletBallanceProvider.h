#pragma once

#include <QObject>
#include <entities/WalletId.h>
#include <entities/Wallet.h>

class IWalletBallanceProvider : public QObject {

    Q_OBJECT

public:
    virtual int64_t getWalletBallance(const WalletId& walletId) = 0;
    virtual const std::vector<WalletInfo> & walletsInfo() = 0;
signals:
    void ballanceChanged();
};

using IWalletBallanceProviderPtr = std::shared_ptr<IWalletBallanceProvider>;
