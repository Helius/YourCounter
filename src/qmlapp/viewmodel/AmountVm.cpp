#include "AmountVm.h"
#include <QLocale>
namespace AmountVM {

QString formatAmount(const int64_t amount)
{
    auto locale = QLocale("ru_RU");
    return locale.toString(amount / 100.0, 'f', 2);
}

int8_t amountFromString(const QString& string)
{
    bool ok = false;
    auto value = static_cast<int8_t>(string.toFloat(&ok) * 100);
    Q_ASSERT(ok);
    return value;
}

}
