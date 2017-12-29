//
//  Terrain.hpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/29/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp

#include "PerlinNoise.h"
#include <iostream>
using namespace std;

enum TerrainTileType {
    GROUND,
    TREE,
    WATER
};

struct TerrainTile {
    float elevation;
    TerrainTileType type;
    
};

class Terrain
{
private:
    vector<vector<TerrainTile>> tileMap;

public:
    Terrain(unsigned int size);
};

#endif /* Terrain_hpp */
