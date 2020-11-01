#include "tilesholder.h"
#include "tile.h"

#include <algorithm>
#include <random>

TilesHolder::TilesHolder(int nImagesNumber, QObject* pParent /*= nullptr*/)
    : QObject(pParent)
    , m_nFirst(-1)
    , m_nSecond(-1)
    , m_nAttemptsNumber(0)
    , m_bFinished(false)
{
    Q_ASSERT(nImagesNumber > 0);

    connect(&m_closeTimer, &QTimer::timeout, this, &TilesHolder::OnCloseTimer);
    m_closeTimer.setSingleShot(true);
    m_closeTimer.setInterval(1000);

    m_vTiles.reserve(nImagesNumber * 2);
    for (int i = 0; i < nImagesNumber; ++i) {
        m_vTiles.push_back(Tile(i));
        m_vTiles.push_back(Tile(i));
    }

    shuffleTiles();
}

int TilesHolder::tilesCount() const
{
    return m_vTiles.size();
}

const Tile &TilesHolder::tileAt(int i) const
{
    static Tile invalidTile;
    if (i < 0 || i >= tilesCount())
        return invalidTile;
    return m_vTiles.at(i);
}

Tile &TilesHolder::tileAt(int i)
{
    static Tile invalidTile;
    if (i < 0 || i >= tilesCount())
        return invalidTile;
    return m_vTiles[i];
}

void TilesHolder::processTile(int nIndex)
{
    if (isFilled())
        return;

    const Tile& rTile = tileAt(nIndex);
    if (!rTile.isValid() || rTile.state() == TileState::Matched)
        return;

    if (m_nFirst == -1)
        m_nFirst = nIndex;
    else
        m_nSecond = nIndex;

    setTileState(nIndex, TileState::Open);

    if (isFilled()) {
        setAttemptsNumber(m_nAttemptsNumber + 1);

        if (!match())
            m_closeTimer.start();
        else
            updateIsGameFinished();
    }
}

bool TilesHolder::isFilled() const {
    return m_nFirst != -1 && m_nSecond != -1;
}

void TilesHolder::updateIsGameFinished()
{
    bool bFinished = true;
    for (const Tile& rTile : m_vTiles)
    {
        if (rTile.state() != TileState::Matched)
        {
            bFinished = false;
            break;
        }
    }

    setGameFinished(bFinished);
}

void TilesHolder::setAttemptsNumber(int nNumber)
{
    if (nNumber != m_nAttemptsNumber)
    {
        m_nAttemptsNumber = nNumber;
        emit attemptsNumberChanged(m_nAttemptsNumber);
    }
}

void TilesHolder::setGameFinished(bool bFinished)
{
    if (bFinished != m_bFinished)
    {
        m_bFinished = bFinished;
        emit gameFinishedChanged(m_bFinished);
    }
}

int TilesHolder::attemptsNumber() const
{
    return m_nAttemptsNumber;
}

bool TilesHolder::gameFinished() const
{
    return m_bFinished;
}

void TilesHolder::reset() {
    m_nFirst = -1;
    m_nSecond = -1;

    for (auto& rTile : m_vTiles) {
        rTile.reset();
    }

    setAttemptsNumber(0);
    setGameFinished(false);
}

bool TilesHolder::match() {

    if (m_nFirst == -1 || m_nSecond == -1)
        return false;

    Tile& rFirst = tileAt(m_nFirst);
    Tile& rSecond = tileAt(m_nSecond);

    if (rFirst.isValid() && rSecond.isValid())
    {
        if (rFirst.id() == rSecond.id())
        {
            setTileState(m_nFirst, TileState::Matched);
            setTileState(m_nSecond, TileState::Matched);
            m_nFirst = -1; m_nSecond = -1;
            return true;
        }
    }

    return false;
}

void TilesHolder::shuffleTiles()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_vTiles.begin(), m_vTiles.end(), g);
}

void TilesHolder::setTileState(int nIndex, TileState enState, bool bEmit /*= true*/)
{
    Tile& rTile = tileAt(nIndex);

    if (!rTile.isValid())
        return;

    if (rTile.state() == enState)
        return;

    rTile.setState(enState);
    if (bEmit) emit tileChanged(nIndex);
}

void TilesHolder::OnCloseTimer()
{
    if (m_nFirst != -1) setTileState(m_nFirst, TileState::Closed);
    if (m_nSecond != -1) setTileState(m_nSecond, TileState::Closed);
    m_nFirst = -1; m_nSecond = -1;
}
