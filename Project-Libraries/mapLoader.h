// mapLoader.h
// Bruce Smith
// 2024-11-29
//
// Header for mapLoader.cpp
// Handles loading and unloading of map data stored..
// .. in the JSON format

#pragma once

#include <SFML/Graphics.hpp>   // For window/rending calls
#include <nlohmann/json.hpp>   // For JSON parsing
#include <fstream>   // For opening files
#include <vector>   // For vector
#include <string>   // For string

struct Map {
   sf::Texture texture_atlas; // Store texture atlas
   std::vector<std::vector<int>> MapData; // Matrix for storing tile data
};

Map loadMap(const std::string& filename);
