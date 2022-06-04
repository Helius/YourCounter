#pragma once
#include <QString>

class WalletId {
public:
    explicit WalletId() = default;
    explicit WalletId(const QString& id)
        : m_id(id)
    {
    }

    operator bool() const { return !m_id.isEmpty(); }
    QString toString() const { return m_id; }
    bool operator==(const WalletId& other) const
    {
        return m_id == other.toString();
    }

private:
    QString m_id;
};
