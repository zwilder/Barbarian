#include "../include/game_map.hpp"

GameMap::GameMap(int w, int h) : width_(w), height_(h)
{
    initTiles_();
    makeMap_();
}

void GameMap::initTiles_()
{
    int wallFlags = (Tile::Flags::BLOCKS_MOVEMENT | Tile::Flags::BLOCKS_LIGHT);
    wsl::Glyph wallGlyph = wsl::Glyph('#', wsl::Color(0,0,50));
    Tile wallTile = Tile(wallFlags, wallGlyph);
    tiles.assign(width_ * height_, wallTile);
}

void GameMap::createRoom_(wsl::Rect room)
{
    for(int x = room.x1 + 1; x < room.x2; ++x)
    {
        for(int y = room.y1 + 1; y < room.y2; ++y)
        {
            tiles[index(x,y)] = Tile(Tile::Flags::NONE);
        }
    }
}

void GameMap::hTunnel_(int x1, int x2, int y)
{
    int min = (x1 < x2 ? x1 : x2);
    int max = (x1 > x2 ? x1 : x2);
    for(int i = min; i <= max; ++i)
    {
        tiles[index(i,y)] = Tile(Tile::Flags::NONE);
    }
}

void GameMap::vTunnel_(int y1, int y2, int x)
{
    int min = (y1 < y2 ? y1 : y2);
    int max = (y1 > y2 ? y1 : y2);
    for(int i = min; i <= max; ++i)
    {
        tiles[index(x,i)] = Tile(Tile::Flags::NONE);
    }
}

void GameMap::makeMap_()
{
    wsl::Rect room1 = wsl::Rect(20,15,10,15);
    wsl::Rect room2 = wsl::Rect(35,15,10,15);

    createRoom_(room1);
    createRoom_(room2);

    hTunnel_(25,40,23);
}

bool GameMap::isBlocked(int x, int y)
{
    bool success = false;
    if(tiles[index(x,y)].blocksMovement())
    {
        success = true;
    }
    return success;
}
