// map_loader.h
// Bruce Smith
// 2024-11-29
//
// Header for map_loader.cpp
// Handles loading and unloading of map data stored..
// .. in the JSON format

#pragma once

#include <SFML/Graphics.hpp>   // For window/rending calls
#include <nlohmann/json.hpp>   // For JSON parsing
#include <fstream>   // For opening files
#include <vector>   // For vector
#include <string>   // For string
#include "npc.h"   // For npc related functions and data

struct Map {
   sf::Texture texture_atlas; // Store texture atlas
   unsigned int texture_atlas_width; // Store texture atlas width in tiles
   unsigned int texture_atlas_height; // Store texture atlas height in tiles
   unsigned int map_width; // Store map width in tiles
   unsigned int map_height; // Store map width in tiles
   std::vector<std::vector<int>> MapData; // Matrix for storing tile data
   std::vector<int> CollisionData; // Array for storing collision data
   std::vector<int> SubareaLocations; // Locations of sub areas in a map
   std::vector<std::string> SubareaSources; // Store source path for subareas
   std::vector<npc> NPCList; // Store list of NPC's and their data
   std::string north_map_source; // Store source path for north map
   std::string west_map_source;
   std::string east_map_source;
   std::string south_map_source;
   int north_x_entrance; // Store start of north entrance on the x
   int west_y_entrance; // Store start of west entrance on the y
   int east_y_entrance;
   int south_x_entrance;
};

Map loadMap(const std::string& filename);

void unloadMap(Map& map);
