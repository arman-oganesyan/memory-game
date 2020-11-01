#include "tilesholder.h"
#include "tile.h"

void TilesHolder::process(const TilePtr& spTile) {
    if (!spTile || isFilled())
        return;

    spTile->setState(TileState::Open);

    if (!m_wpFirst) {
        m_wpFirst = spTile;
    }
    else if (!m_wpSecond) {
        m_wpSecond = spTile;
    }
}

bool TilesHolder::isFilled() const {
    return m_wpFirst && m_wpSecond;
}

void TilesHolder::reset() {
    m_wpFirst.clear();
    m_wpSecond.clear();
}

bool TilesHolder::match() {

    TilePtr spFirst = m_wpFirst.toStrongRef();
    TilePtr spSecond = m_wpSecond.toStrongRef();

    if (spFirst && spSecond)
    {
        if (spFirst->id() == spSecond->id())
        {
            spFirst->setState(TileState::Matched);
            spSecond->setState(TileState::Matched);
            return true;
        }
    }

    return false;
}

TilePtr TilesHolder::first() const {
    return m_wpFirst.toStrongRef();
}

TilePtr TilesHolder::second() const {
    return m_wpSecond.toStrongRef();
}
