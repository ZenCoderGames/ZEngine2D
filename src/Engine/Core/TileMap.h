#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

#include "./Engine.h"

class TileMap {
    private:
        std::string m_textureId;
        int m_tileSize;
        int m_scale;

        std::vector<Entity*> m_tiles;

        void AddTile(int sourceX, int sourceY, int x, int y);
    public:
        TileMap(std::string textureId, int scale, int tileSize);
        ~TileMap();

        void LoadData(std::string filePath, int sizeX, int sizeY);
};

#endif