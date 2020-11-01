#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractItemModel>

#include "tiles/tilesholder.h"


class GameModel : public QAbstractItemModel
{
    Q_OBJECT

    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int attemptsNumber READ attemptsNumber NOTIFY attemptsNumberChanged)
    Q_PROPERTY(bool gameFinished READ gameFinished NOTIFY gameFinishedChanged)

    enum Role {
        Role_Id = Qt::UserRole + 1,
        Role_Open,
        Role_Matched,

        // ALWAYS AT THE END
        Role_Count
    };

public:
    GameModel(QObject* pParent = nullptr);

    Q_INVOKABLE void start();
    Q_INVOKABLE void processClicked(int index);

    int dimension() const;
    int attemptsNumber() const;
    bool gameFinished() const;

    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void attemptsNumberChanged(int);
    void gameFinishedChanged(bool);

private slots:
    void OnTileChanged(int nIndex);

private:
    TilesHolder m_holder;
};

#endif // GAMEMODEL_H
