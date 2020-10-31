#include "tile.h"

Tile::Tile(int nId)
    : m_nId(nId)
    , m_enState(TileState::Closed)
{

}

void Tile::reset()
{
    m_enState = TileState::Closed;
}

bool Tile::isClosed() const
{
    return state() == TileState::Closed;
}

int Tile::id() const
{
    return m_nId;
}

TileState Tile::state() const
{
    return m_enState;
}

void Tile::setState(TileState enState)
{
    m_enState = enState;
}
