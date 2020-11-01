#include "gamemodel.h"

#include "tiles/tile.h"


const int m_kDimension = 4; // ONLY EVEN NUMBERS
const int m_kImagesNumber = (m_kDimension * m_kDimension) / 2;

GameModel::GameModel(QObject* pParent /*= nullptr*/)
    : QAbstractItemModel(pParent)
    , m_holder(m_kImagesNumber)
{
    connect(&m_holder, &TilesHolder::tileChanged, this, &GameModel::OnTileChanged);
    connect(&m_holder, &TilesHolder::attemptsNumberChanged, this, &GameModel::attemptsNumberChanged);
    connect(&m_holder, &TilesHolder::gameFinishedChanged, this, &GameModel::gameFinishedChanged);
}

void GameModel::start()
{
    beginResetModel();
    m_holder.reset();
    endResetModel();
}

void GameModel::processClicked(int nIndex)
{
    m_holder.processTile(nIndex);
}

int GameModel::dimension() const
{
    return m_kDimension;
}

int GameModel::attemptsNumber() const
{
    return m_holder.attemptsNumber();
}

bool GameModel::gameFinished() const
{
    return m_holder.gameFinished();
}

QModelIndex GameModel::index(int row, int column, const QModelIndex &parent) const
{
    if (column != 0 || parent.isValid())
        return QModelIndex();

    if (row < 0 || row >= m_holder.tilesCount())
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
    return m_holder.tilesCount();
}

int GameModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_holder.tilesCount() || index.column() > 0)
        return QVariant();

    if (role >= Role_Id && role < Role_Count) {
        const auto& rTile = m_holder.tileAt(index.row());
        switch (role) {
            case Role_Id:       return rTile.id();
            case Role_Open:     return !rTile.isClosed();
            case Role_Matched:  return rTile.state() == TileState::Matched;
            default:            return QVariant();
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

void GameModel::OnTileChanged(int nIndex)
{
    emit dataChanged(index(nIndex, 0, QModelIndex()), index(nIndex, columnCount(QModelIndex()) - 1, QModelIndex()));
}
