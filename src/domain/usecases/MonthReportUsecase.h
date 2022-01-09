#pragma once

#include <QDate>
#include <QObject>
#include <repos/IEntityRepo.h>

struct CategoryTotalAmount {
    QString groupName;
    QString categoryName;
    int64_t totalAmount = 0;
};

class MonthReportUsecase
    : public QObject {
    Q_OBJECT

public:
    using CategoriesTotalAmount = std::vector<CategoryTotalAmount>;

    MonthReportUsecase(IEntityRepoPtr repo);

    CategoriesTotalAmount generateMonthReport(const QDate& monthDate);

private:
    std::pair<QString, QString> groupCategoryNameById(const QString& id);

private:
    IEntityRepoPtr m_repo;
};

using MonthReportUsecaseUnq = std::unique_ptr<MonthReportUsecase>;