#pragma once

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <usecases/MonthReportUsecase.h>

class MonthReportModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles {
        GroupName = Qt::UserRole + 1,
        CategoryName,
        TotalAmount,
    };

    explicit MonthReportModel(MonthReportUsecaseUnq usecase);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    MonthReportUsecaseUnq m_usecase;
    MonthReportUsecase::CategoriesTotalAmount m_amounts;
};

// sorting model for section

class MonthReportSortedModel : public QSortFilterProxyModel {
    Q_OBJECT
public:
    MonthReportSortedModel(MonthReportUsecaseUnq usecase);

private:
    MonthReportModel* m_sourceModel;
};

using MonthReportSortedModelUnq = std::unique_ptr<MonthReportSortedModel>;