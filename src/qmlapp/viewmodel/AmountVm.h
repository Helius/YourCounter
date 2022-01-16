#pragma once

#include <QString>

namespace AmountVM {

QString formatAmount(const int64_t amount);
int8_t amountFromString(const QString& string);
}