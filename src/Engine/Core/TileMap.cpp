#include "TileMap.h"

#include <iostream>
#include <fstream>
#include "../Components/TileComponent.h"

TileMap::TileMap(std::string textureId, int scale, int tileSize) {
    m_textureId = textureId;
    m_tileSize = tileSize;
    m_scale = scale;
}

void TileMap::LoadData(std::string filePath, int sizeX, int sizeY) {
    std::fstream mapData;
    mapData.open(filePath);

    for(int r=0; r<sizeY; ++r) {
        for(int c=0; c<sizeX; ++c) {
            char ch;
            mapData.get(ch);
            int sourceRectY = atoi(&ch) * m_tileSize;
            mapData.get(ch);
            int sourceRectX = atoi(&ch) * m_tileSize;
            AddTile(sourceRectX, sourceRectY, c * m_tileSize * m_scale, r * m_tileSize * m_scale);
            mapData.ignore();
        }
    }

    mapData.close();
}

void TileMap::AddTile(int sourceX, int sourceY, int x, int y) {
    Entity* tile = &(Engine::entityManager->AddEntity(std::string("tile_") + std::to_string(x) + std::to_string(y), LAYER_TILE_MAP));
    tile->AddComponent<TileComponent>(m_textureId, sourceX, sourceY, m_tileSize, x, y, m_scale);
    m_tiles.emplace_back(tile);
}