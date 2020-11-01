#ifndef TILE_H
#define TILE_H

#include "tilestate.h"

class Tile {
public:
    Tile();
    Tile(int nId);

    void reset();
    bool isValid() const;
    bool isClosed() const;
    int id() const;
    TileState state() const;
    void setState(TileState enState);

private:
    int m_nId;
    bool m_bValid;
    TileState m_enState;
};

#endif // TILE_H
