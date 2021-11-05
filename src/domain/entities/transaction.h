#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Category.h"
#include "interval.h"
#include <QDateTime>
#include <QString>
#include <utility>

class Transaction {

public:
  QString id;
  float amount;
  QDateTime when;
  QString categoryId;
  QString who;
  QString comment;

  Transaction() = delete;
  Transaction(const QString &id, float amount, const QDateTime &when,
              const QString &categoryId, const QString &who = QString(),
              const QString &comment = QString())
      : id(id), amount(amount), when(when), categoryId(categoryId), who(who),
        comment(comment) {
    Q_ASSERT(!this->id.isEmpty());
    Q_ASSERT(!this->categoryId.isEmpty());
    Q_ASSERT(abs(this->amount) > 0.001);
  }

  Transaction(const Transaction &other) = default;
  Transaction &operator=(const Transaction &) = default;

  operator bool() const {
    return !id.isEmpty() && qFuzzyCompare(amount, 0) && when.isValid();
  }

  bool operator==(const Transaction &other) const {
    return id == other.id && qFuzzyCompare(amount, other.amount) &&
           when == other.when && categoryId == other.categoryId &&
           who == other.who && comment == other.comment;
  }
};

using Transactions = std::vector<Transaction>;

#endif // TRANSACTION_H
