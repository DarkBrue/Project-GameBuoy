// project_gamebuoy.cpp
// Bruce Smith
// 2024-11-30
//
// Contains main
// Check constants.h for more information on constant variables

#include <iostream> // For IO debugging
#include <SFML/Graphics.hpp>   // For window/rendering calls
#include <vector>   // For vector
#include "Project-Libraries/resize_window.h"   // Handles resizing screen
#include "Project-Libraries/map_loader.h"   // Handles loading and unloading map data
#include "Project-Libraries/constants.h"   // Access to commonly used variables
#include "Project-Libraries/visible_grid.h" // For VisibleGrid functions

// Don't touch this variable unless you know what you are doing
// Used to scale window and sprites
int scale_factor = 2;
int getScaleFactor()
{
   return scale_factor;
}

// Function: handleKeyPress
// - handles event where key is pressed (generally user input)
void handleKeyPress(sf::Keyboard::Key input, sf::RenderWindow& window, Player& player,
                    const std::vector<sf::Texture>& Textures, const Map& map,
                    const sf::Texture& black_texture,
                    sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH])
{
   // Events that require updating the entire VisibleGrid
   if (input == LEFT_KEY || input == RIGHT_KEY
       || input == UP_KEY || input == DOWN_KEY)
   {
      if (input == RIGHT_KEY)
      {
         translateVisibleGridRight(VisibleGrid, map, Textures, player, black_texture);
         player.pos_X++; // Increment players x-position in the map
      }
      else if (input == LEFT_KEY)
      {
         translateVisibleGridLeft(VisibleGrid, map, Textures, player, black_texture);
         player.pos_X--; // Increment players x-position in the map
      }

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
   // Create a black image, our "missing texture"
   sf::Image all_black;
   all_black.create(TILE_WIDTH * getScaleFactor(),
                    TILE_HEIGHT * getScaleFactor(),
                    sf::Color::Black);

   sf::Texture black_texture;
   if(!black_texture.loadFromImage(all_black))
   {
      return EXIT_FAILURE;
   }

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
   player.pos_Y = 5;
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
            handleKeyPress(event.key.code, window, player,
                           Textures, CurrentMap, black_texture, VisibleGrid);
         }
      } // End of event poll
   } // End of game loop

   return EXIT_SUCCESS;
}
