// npc.h
// Bruce Smith
// 2024-12-17
//
// Header file for npc.cpp
// Handles movement and anything else related to NPC's

#pragma once

#include <string>   // For std::string

struct npc
{
   int pos_X; // NPC x position within a map
   int pos_Y; // NPC y position within a map
   sf::Sprite npc_sprite;
   //std::vector<sf::Texture> NPCAnimations (FILL LATER);
   std::vector<std::string> NPCDialogue;
};
