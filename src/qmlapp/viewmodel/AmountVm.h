#pragma once

#include <QString>

namespace AmountVM {

QString formatAmount(const int64_t amount);
int64_t amountFromString(const QString& string);
}