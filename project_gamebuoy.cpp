// project_gamebuoy.cpp
// Bruce Smith
// 2024-11-30
//
// Contains main
// Check constants.h for more information on constant variables

#include <iostream> // For IO debugging
#include <SFML/Graphics.hpp>   // For window/rendering calls
#include <vector>   // For vector
#include <cmath>   // For abs
#include "Project-Libraries/resize_window.h"   // Handles resizing screen
#include "Project-Libraries/mapLoader.h"   // Handles loading and unloading map data
#include "Project-Libraries/constants.h"   // Access to commonly used variables

// Don't touch this variable unless you know what you are doing
// Used to scale window and sprites
unsigned int scale_factor = 2;

//struct Player
//{
//   int pos_X; // Player x position within a map
//   int pos_Y; // Player y position within a map
//   sf::Sprite player_sprite;
   //std::vector<sf::Texture> player_animations (FILL LATER);
//};

// Function: drawVisibleGrid
// NOTE: MIGHT TAKE LIST OF NPCS ON SCREEN TO RESIZE
void drawVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                     sf::RenderWindow& window, Player& player)
{
   window.clear();
   // Loop to draw the VisibleGrid
   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         window.draw(VisibleGrid[y][x]);
      }
   }
   window.draw(player.player_sprite);
   window.display();
}

// Function: handleKeyPress
// - handles event where key is pressed (generally user input)
void handleKeyPress(sf::Keyboard::Key input, sf::RenderWindow& window, Player& player,
                    sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH])
{
   // Events that require updating the entire VisibleGrid
   if (input == LEFT_KEY || input == RIGHT_KEY
       || input == UP_KEY || input == DOWN_KEY)
   {
      drawVisibleGrid(VisibleGrid, window, player);
   }

   // Events that require resizing the screen
   else if (input == NUM1_KEY || input == NUM2_KEY || input == NUM3_KEY)
   {
      // Scale factor of the screen and tiles
      if (input == NUM1_KEY)      scale_factor = 1;
      else if (input == NUM2_KEY) scale_factor = 2;
      else if (input == NUM3_KEY) scale_factor = 3;
      resizeWindow(window, player, scale_factor, VisibleGrid);
   }
}

// Function: initializeVisibleGrid
// - initalizes a grid of textures that will be displayed to the window
// - occurs during hard loading zone (e.g. doors)
int initializeVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                          const std::vector<sf::Texture>& Textures,
                          const Map& map, const Player& player)
{
   // Used to determine which tiles in the map data are visible

   // These 4 variables will be used to index map data
   // I really don't want to explain it, maybe sometime later
   int start_X = std::max(player.pos_X - PLAYER_SCREEN_POS_X, 0);
   int end_X   = std::min((int)map.map_width,
                          start_X + VISIBLE_WIDTH);
   int start_Y = std::max(player.pos_Y - PLAYER_SCREEN_POS_Y, 0);
   int end_Y   = std::min((int)map.map_height,
                          start_Y + VISIBLE_HEIGHT);

   // Helps translate map coordinates to VisibleGrid coordinates
   int offset_X = PLAYER_SCREEN_POS_X - player.pos_X;
   int offset_Y = PLAYER_SCREEN_POS_Y - player.pos_Y;

   // Cut end short so we don't index off grid
   if (offset_X + end_X - 1 >= VISIBLE_WIDTH) end_X -= offset_X;
   if (offset_Y + end_Y - 1 >= VISIBLE_HEIGHT) end_Y -= offset_Y;

   for (int y = start_Y; y < end_Y; y++)
   {
      for (int x = start_X; x < end_X; x++)
      {
         VisibleGrid[y + offset_Y][x + offset_X].setTexture(Textures[map.MapData[y][x]]);
      }
   }

   return 0;
}

// Function: extractTextures
// - extracts textures from texture atlas associated with a map
void extractTextures(std::vector<sf::Texture>& Textures, const Map& map)
{
   for (int y = 0; y < map.texture_atlas_height; y++)
   {
      for (int x = 0; x < map.texture_atlas_width; x++)
      {
         // Create a cookie cutter
         sf::IntRect SubRect(x * TILE_WIDTH, y * TILE_HEIGHT,
                                 TILE_WIDTH, TILE_HEIGHT);

         sf::Texture sub_texture;

         // Cookie cut textures from atlas
         if (sub_texture.loadFromImage(map.texture_atlas.copyToImage(), SubRect))
         {
            Textures.push_back(std::move(sub_texture));
         }
      }
   }
}

int main()
{
   // Create grid that will be displayed to the window
   // NOTE: SHOULD ONLY CONTAIN GAME TERRAIN, NOT MENUS
   sf::Sprite VisibleGrid[VISIBLE_HEIGHT][VISIBLE_WIDTH];

   // Set up tile size/location
   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         VisibleGrid[y][x].setScale(scale_factor, scale_factor);
         VisibleGrid[y][x].setPosition(x * TILE_WIDTH * scale_factor,
                                       y * TILE_HEIGHT * scale_factor);
      }
   }

   Map CurrentMap = loadMap("Map-Data/map_02.json");

   // Will store textures from a texture atlas associated to map data
   std::vector<sf::Texture> Textures;

   extractTextures(Textures, CurrentMap);

   Player player; // Create player
   sf::Texture player_texture;
   if (!player_texture.loadFromFile("Assets/player.png"))
   {
      return EXIT_FAILURE;
   }
   player_texture.setSmooth(false);   // Disable smooth filter
   player.player_sprite.setTexture(player_texture);
   player.pos_X = 5;
   player.pos_Y = 6;
   player.player_sprite.setScale(scale_factor, scale_factor);
   player.player_sprite.setPosition(PLAYER_SCREEN_POS_X * TILE_WIDTH * scale_factor,
                                    PLAYER_SCREEN_POS_Y * TILE_HEIGHT * scale_factor);

   // Set up grid of viewable tiles
   initializeVisibleGrid(VisibleGrid, Textures, CurrentMap, player);

   // Create main window
   sf::RenderWindow window(sf::VideoMode(DEFAULT_WINDOW_WIDTH * scale_factor,
                                         DEFAULT_WINDOW_HEIGHT * scale_factor),
                                         "GameBuoy");

   // Start game loop
   while (window.isOpen())
   {
      // Process events
      sf::Event event;
      while (window.pollEvent(event))
      {
         // If we receive a close window event
         if (event.type == sf::Event::Closed) window.close();
         // Check for key presses
         else if (event.type == sf::Event::KeyPressed)
         {
            handleKeyPress(event.key.code, window, player, VisibleGrid);
         }
      } // End of event poll
   } // End of game loop

   return EXIT_SUCCESS;
}
