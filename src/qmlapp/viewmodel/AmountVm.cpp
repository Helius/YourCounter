#include "AmountVm.h"
#include <QRegularExpression>
#include <QLocale>
namespace AmountVM {

QString formatAmount(const int64_t amount)
{
    auto locale = QLocale("ru_RU");
    return locale.toString(amount / 100.0, 'f', 2);
}

int64_t amountFromString(const QString& string)
{
    auto trimmed = string;
    trimmed.remove(QRegularExpression("\\s"));
    bool minus = trimmed.startsWith("-");
    trimmed.remove("-");
    QStringList parts = trimmed.split(QRegularExpression("[.,]"), Qt::SkipEmptyParts);
    qulonglong i, f = 0;
    Q_ASSERT(parts.size() > 0);
    i = parts.at(0).toULongLong();
    if (parts.size() > 1) {
        auto fStr = parts.at(1).left(2);
        f = fStr.toUInt();
    }

    return minus ? -(i * 100 + f) : (i * 100 + f);
}

}
