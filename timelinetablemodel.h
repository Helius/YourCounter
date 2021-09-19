#ifndef TIMELINETABLEMODEL_H
#define TIMELINETABLEMODEL_H

#include <QAbstractListModel>

class ITransactionRepo;

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
    TimeLineTableModel(ITransactionRepo *repo, QObject *parent = nullptr);
public slots:
    int getColumnWidth(int column);


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QString calcAmount(int row, int col) const;
    ITransactionRepo * m_repo;

};

#endif // TIMELINETABLEMODEL_H
