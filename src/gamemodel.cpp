#include "gamemodel.h"

#include <algorithm>
#include <random>

#include "tile.h"
#include "tilesholder.h"

GameModel::GameModel(QObject* pParent /*= nullptr*/)
    : QAbstractItemModel(pParent)
    , m_nAttemptsNumber(0)
    , m_bGameFinished(false)
{
    m_vTiles.reserve(m_kTilesNumber);

    for (int i = 0; i < m_kImagesNumber; ++i) {
        m_vTiles.push_back(QSharedPointer<Tile>::create(i));
        m_vTiles.push_back(QSharedPointer<Tile>::create(i));
    }

    connect(&m_closeTimer, &QTimer::timeout, this, &GameModel::OnCloseTimer);
    m_closeTimer.setSingleShot(true);
    m_closeTimer.setInterval(1000);

    shuffleTiles();
}

void GameModel::start()
{
    m_closeTimer.stop();
    m_holder.reset();
    setAttemptsNumber(0);
    setGameFinished(false);

    beginResetModel();

    for (auto spTile : m_vTiles) {
        if (spTile)
            spTile->reset();
    }

    shuffleTiles();
    endResetModel();
}

void GameModel::processClicked(int nIndex)
{
    if (m_holder.isFilled() || m_closeTimer.isActive())
        return;

    if (nIndex < 0 || nIndex >= m_vTiles.size())
        return;

    auto spTile = m_vTiles[nIndex];
    if (!spTile)
        return;

    if (!spTile->isClosed())
        return;

    m_holder.process(spTile);

    emitTilesChanged(spTile);

    if (m_holder.isFilled())
    {
        if (m_holder.match()) {
            emitTilesChanged({m_holder.first(), m_holder.second()});
            m_holder.reset();
            verifyFinished();
        }
        else
            m_closeTimer.start();

        incrementAttempts();
    }
}

int GameModel::dimension() const
{
    return m_kDimension;
}

int GameModel::attemptsNumber() const
{
    return m_nAttemptsNumber;
}

bool GameModel::gameFinished() const
{
    return m_bGameFinished;
}

void GameModel::setAttemptsNumber(int nNumber)
{
    if (nNumber != m_nAttemptsNumber)
    {
        m_nAttemptsNumber = nNumber;
        emit attemptsNumberChanged(m_nAttemptsNumber);
    }
}

void GameModel::setGameFinished(bool bFinished)
{
    if (bFinished != m_bGameFinished)
    {
        m_bGameFinished = bFinished;
        emit gameFinishedChanged(m_bGameFinished);
    }
}

QModelIndex GameModel::index(int row, int column, const QModelIndex &parent) const
{
    if (column != 0 || parent.isValid())
        return QModelIndex();

    if (row < 0 || row >= m_vTiles.size())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex GameModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_vTiles.size();
}

int GameModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_vTiles.size() || index.column() > 0)
        return QVariant();

    if (role >= Role_Id && role < Role_Count) {
        if (auto spTile = m_vTiles[index.row()])
        {
            switch (role) {
                case Role_Id:       return spTile->id();
                case Role_Open:     return !spTile->isClosed();
                case Role_Matched:  return spTile->state() == TileState::Matched;
                default:            return QVariant();
            }
        }
    }

    return QVariant();
}

QHash<int, QByteArray> GameModel::roleNames() const
{
    return {
        {Role_Id, "id"},
        {Role_Open, "open"},
        {Role_Matched, "matched"}
    };
}

void GameModel::OnCloseTimer()
{
    closeTile(m_holder.first());
    closeTile(m_holder.second());
    m_holder.reset();
}

void GameModel::verifyFinished() {
    bool bFinished = true;

    for (const TilePtr& spTile : m_vTiles) {
        if (!spTile || spTile->state() != TileState::Matched) {
            bFinished = false;
            break;
        }
    }

    setGameFinished(bFinished);
}

void GameModel::shuffleTiles()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_vTiles.begin(), m_vTiles.end(), g);
}

void GameModel::closeTile(const TilePtr &spTile)
{
    if (!spTile || spTile->isClosed())
        return;

    spTile->setState(TileState::Closed);
    emitTilesChanged(spTile);
}

void GameModel::emitTilesChanged(const TilePtr &spTile)
{
    emitTilesChanged({spTile});
}

void GameModel::emitTilesChanged(std::initializer_list<TilePtr> listTiles)
{
    for (const TilePtr& spTile : listTiles) {
        if (!spTile)
            continue;

        int nIndex = m_vTiles.indexOf(spTile);
        if (nIndex == -1)
            continue;

        emit dataChanged(index(nIndex, 0, QModelIndex()), index(nIndex, columnCount(QModelIndex()) - 1, QModelIndex()));
    }
}

void GameModel::incrementAttempts()
{
    setAttemptsNumber(attemptsNumber() + 1);
}
