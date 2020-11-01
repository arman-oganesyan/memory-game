#ifndef TILESHOLDER_H
#define TILESHOLDER_H

#include <QObject>
#include <QVector>
#include <QTimer>

#include "tile.h"

class TilesHolder : public QObject
{
    Q_OBJECT
public:
    explicit TilesHolder(int nImagesNumber, QObject* pParent = nullptr);

    int tilesCount() const;
    const Tile& tileAt(int i) const;
    Tile& tileAt(int i);

    void processTile(int nIndex);
    void reset();

    int attemptsNumber() const;
    bool gameFinished() const;

private:
    bool match();
    void shuffleTiles();
    void updateIsGameFinished();
    bool isFilled() const;

    void setTileState(int nIndex, TileState enState, bool bEmit = true);
    void setAttemptsNumber(int nNumber);
    void setGameFinished(bool bFinished);

private slots:
    void OnCloseTimer();

signals:
    void tileChanged(int nIndex);
    void attemptsNumberChanged(int nIndex);
    void gameFinishedChanged(bool bFinished);

private:
    QTimer m_closeTimer;
    QVector<Tile> m_vTiles;
    int m_nFirst;
    int m_nSecond;
    int m_nAttemptsNumber;
    bool m_bFinished;
};

#endif // TILESHOLDER_H
