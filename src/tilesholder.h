#ifndef TILESHOLDER_H
#define TILESHOLDER_H

#include "tile_fwd.h"

class TilesHolder {
public:
    void process(const TilePtr& spTile);

    bool reset();
    bool match();

    bool isFilled() const;
    TilePtr first() const;
    TilePtr second() const;
private:
    TileWPtr m_wpFirst;
    TileWPtr m_wpSecond;
};

#endif // TILESHOLDER_H
