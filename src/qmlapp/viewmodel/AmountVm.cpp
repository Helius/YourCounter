#include "AmountVm.h"

namespace AmountVM {

QString formatAmount(const int64_t amount)
{
    return QString("%1,%2")
        .arg(amount / 100, 0, 10)
        .arg(abs(amount % 100), 2, 10, QLatin1Char('0'));
}

}
