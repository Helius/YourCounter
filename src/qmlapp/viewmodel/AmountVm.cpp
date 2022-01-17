#include "AmountVm.h"
#include <QLocale>
namespace AmountVM {

QString formatAmount(const int64_t amount)
{
    auto locale = QLocale("ru_RU");
    return locale.toString(amount / 100.0, 'f', 2);
}

int64_t amountFromString(const QString& string)
{
    bool ok = false;
    auto locale = QLocale("ru_RU");
    auto value = static_cast<int64_t>(locale.toDouble(string, &ok) * 100);
    if (!ok) {
        qCritical() << "Can't parse amount from:[" << string << "]";
        Q_ASSERT(ok);
    }
    return value;
}

}
