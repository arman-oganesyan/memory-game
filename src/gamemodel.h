#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractItemModel>
#include <QTimer>

#include "tilesholder.h"


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
    void OnCloseTimer();

private:
    // property setters
    void setAttemptsNumber(int nNumber);
    void setGameFinished(bool bFinished);

    void verifyFinished();
    void shuffleTiles();
    void closeTile(const TilePtr& spTile);
    void emitTilesChanged(const TilePtr& spTile);
    void emitTilesChanged(std::initializer_list<TilePtr> listTiles);
    void incrementAttempts();

private:

    const int m_kDimension = 10; // ONLY EVEN NUMBERS
    const int m_kImagesNumber = (m_kDimension * m_kDimension) / 2;
    const int m_kTilesNumber = m_kImagesNumber * 2;

    QVector<QSharedPointer<Tile>> m_vTiles;
    TilesHolder m_holder;
    QTimer m_closeTimer;

    int m_nAttemptsNumber;
    bool m_bGameFinished;
};

#endif // GAMEMODEL_H
