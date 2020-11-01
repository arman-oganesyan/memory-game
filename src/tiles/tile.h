#ifndef TILE_H
#define TILE_H

#include "tilestate.h"

class Tile {
public:
    explicit Tile(int nId);

    void reset();
    bool isClosed() const;
    int id() const;
    TileState state() const;
    void setState(TileState enState);

private:
    int m_nId;
    TileState m_enState;
};

#endif // TILE_H
