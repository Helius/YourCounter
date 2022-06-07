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

    int monthIndex() const;
    void setMonthIndex(int newMonthIndex);
    void updateTotal();

signals:
    void monthIndexChanged();
    void numbersChanged(int64_t, int64_t, int64_t);

private:
    QDate calcReportMonth() const;

private:
    MonthReportUsecaseUnq m_usecase;
    MonthReportUsecase::CategoriesTotalAmount m_amounts;
    int m_monthIndex = QDateTime::currentDateTime().date().month();
};

// sorting model for section

class MonthReportSortedModel : public QSortFilterProxyModel {

    Q_OBJECT

    Q_PROPERTY(int monthIndex READ monthIndex WRITE setMonthIndex NOTIFY monthIndexChanged FINAL)
    Q_PROPERTY(QString earn MEMBER m_earn NOTIFY numbersChanged FINAL)
    Q_PROPERTY(QString spend MEMBER m_spend NOTIFY numbersChanged FINAL)
    Q_PROPERTY(QString diff MEMBER m_diff NOTIFY numbersChanged FINAL)

public:
    MonthReportSortedModel(MonthReportUsecaseUnq usecase);

    int monthIndex() const;
    Q_INVOKABLE void setMonthIndex(int newMonthIndex);

signals:
    void monthIndexChanged();
    void numbersChanged();

private:
    MonthReportModel* m_sourceModel;
    QString m_earn;
    QString m_spend;
    QString m_diff;
};

using MonthReportSortedModelUnq = std::unique_ptr<MonthReportSortedModel>;