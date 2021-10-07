#pragma once

class TransactionRequest {

public:
    float amount;
    QDateTime when;
    QString categoryId;
    QString who;
    QString comment;

    TransactionRequest() = delete;
    TransactionRequest(float amount, const QDateTime & when, const QString & categoryId, const QString & who = QString(), const QString & comment = QString())
            : amount(amount)
            , when(when)
            , categoryId(categoryId)
            , who(who)
            , comment(comment)
    {
        Q_ASSERT(!categoryId.isEmpty());
        Q_ASSERT(abs(amount) > 0.001);
    }
};
