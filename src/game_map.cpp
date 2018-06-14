#include "../include/game_map.hpp"

GameMap::GameMap(int w, int h) : width_(w), height_(h)
{
    tiles.assign(width_ * height_, Tile(Tile::Flags::NONE));
    initTiles_();
}

void GameMap::initTiles_()
{
    tiles[index(30,22)] = Tile((Tile::Flags::BLOCKS_MOVEMENT | Tile::Flags::BLOCKS_LIGHT), wsl::Glyph('#'));
    tiles[index(31,22)] = Tile((Tile::Flags::BLOCKS_MOVEMENT | Tile::Flags::BLOCKS_LIGHT), wsl::Glyph('#'));
    tiles[index(32,22)] = Tile((Tile::Flags::BLOCKS_MOVEMENT | Tile::Flags::BLOCKS_LIGHT), wsl::Glyph('#'));
}
