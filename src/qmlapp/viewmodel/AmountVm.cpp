#include "AmountVm.h"
#include <QLocale>
namespace AmountVM {

QString formatAmount(const int64_t amount)
{
    auto locale = QLocale("ru_RU");
    return locale.toString(amount / 100.0, 'f', 2);
}

}
