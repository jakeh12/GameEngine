//
//  Terrain.cpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/29/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//

#include "Terrain.hpp"

Terrain::Terrain(unsigned int size)
{
    tileMap.resize(size);
    for(int i = 0; i < size; i++)
    {
        tileMap[i].resize(size);
    }
    
    unsigned int seed = 237;
    PerlinNoise noiseGenerator(seed);
    
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            double nx = (float)x/(float)size - 0.5;
            double ny = (float)y/(float)size - 0.5;
            tileMap[y][x].elevation = noiseGenerator.noise(nx, ny, 0.8);
        }
    }
    
    for (int y = 0;  y < size; y++) {
        for (int x = 0; x < size; x++) {
            cout << tileMap[y][x].elevation << "\t";
        }
        cout << endl;
    }
}
