#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

#include "./Engine.h"

class Map {
    private:
        std::string m_textureId;
        int m_tileSize;
        int m_scale;

        std::vector<Entity*> m_tiles;

        void AddTile(int sourceX, int sourceY, int x, int y);
    public:
        Map(std::string textureId, int scale, int tileSize);
        ~Map();

        void LoadData(std::string filePath, int sizeX, int sizeY);
};

#endif