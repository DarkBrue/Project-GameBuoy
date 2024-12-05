// map_loader.cpp
// Bruce Smith
// 2024-11-29
//
// Source file for map_loader.h
// Handles loading and unloading of map data stored..
// .. in the JSON format

#include "constants.h"
#include "map_loader.h"
#include <iostream>

// Function: loadMap
// - loads map data from JSON file
// - will return data in form of Map (check mapLoader.h for details)
Map loadMap(const std::string& filename)
{
   std::ifstream file(filename);
   if (!file.is_open())
   {
      std::cerr << "Failed to open JSON file: " << filename << std::endl;
      return {}; // Return empty map
   }

   // Parse JSON file
   nlohmann::json parsed;
   file >> parsed;

   Map map; // Will store map data in our "Map" struct

   std::string texture_path = parsed["texture_atlas"];
   if (!map.texture_atlas.loadFromFile(texture_path))
   {
      std::cerr << "Failed to load texture atlas from: " << texture_path << std::endl;
      return {}; // Return emtpy map
   }

   // Load map data
   map.MapData = parsed["MapData"].get<std::vector<std::vector<int>>>();

   map.map_width = parsed["map_width"];
   map.map_height = parsed["map_height"];

   map.CollisionData = parsed["CollisionData"].get<std::vector<int>>();

   sf::Vector2u size = map.texture_atlas.getSize();
   map.texture_atlas_width = size.x / TILE_WIDTH;
   map.texture_atlas_height = size.y / TILE_HEIGHT;

   return map;
}

// Function: unloadMap
// - pass map and have its data cleared
void unloadMap(Map& map)
{
   map.texture_atlas = sf::Texture();
   map.MapData.clear();
   map.CollisionData.clear();
   map.texture_atlas_width = 0;
   map.texture_atlas_height = 0;
   map.CollisionData.clear();
}
