#pragma once

#include <QObject>
#include <entities/WalletId.h>

class IWalletBallanceProvider : public QObject {

    Q_OBJECT

public:
    virtual int64_t getWalletBallance(const WalletId& walletId) = 0;
signals:
    void ballanceChanged();
};

using IWalletBallanceProviderPtr = std::shared_ptr<IWalletBallanceProvider>;