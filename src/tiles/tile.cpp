#include "tile.h"

Tile::Tile()
    : m_nId(-1)
    , m_bValid(false)
    , m_enState(TileState::Closed)
{

}

Tile::Tile(int nId)
    : m_nId(nId)
    , m_bValid(true)
    , m_enState(TileState::Closed)
{

}

void Tile::reset()
{
    m_enState = TileState::Closed;
}

bool Tile::isValid() const
{
    return m_bValid;
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
