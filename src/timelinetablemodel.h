#ifndef TIMELINETABLEMODEL_H
#define TIMELINETABLEMODEL_H

#include <QAbstractListModel>

class ITransactionRepo;
class IDateColumnAdapter;

class TimeLineTableModel
        : public QAbstractListModel
{
    Q_OBJECT

    enum Roles {
        Amount = Qt::UserRole + 1,
        Color,
        Comment,
        Current,
    };

public:
    TimeLineTableModel(
            ITransactionRepo *repo,
            IDateColumnAdapter * adapter,
            QObject *parent = nullptr);

public slots:
    int getColumnWidth(int column);


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QString calcAmount(int row, int col) const;
    ITransactionRepo * m_repo;
    IDateColumnAdapter * m_dateAdapter;

};

#endif // TIMELINETABLEMODEL_H
