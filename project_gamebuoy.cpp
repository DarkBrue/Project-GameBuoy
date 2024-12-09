// project_gamebuoy.cpp
// Bruce Smith
// 2024-11-30
//
// Contains main
// Check constants.h for more information on constant variables

#include <iostream> // For IO debugging
#include <SFML/Graphics.hpp>   // For window/rendering calls
#include <vector>   // For std::vector
#include <utility>   // For std::swap
#include "Project-Libraries/resize_window.h"   // Handles resizing screen
#include "Project-Libraries/map_loader.h"   // Handles loading and unloading map data
#include "Project-Libraries/constants.h"   // Access to commonly used variables
#include "Project-Libraries/visible_grid.h" // For VisibleGrid functions

// Checks if we loaded map from east of new map
bool map_loaded_from_east = false;
// Checks if we loaded map from west of new map
bool map_loaded_from_west = false;
// Checks if we loaded map from south of new map
bool map_loaded_from_south = false;
// Checks if we loaded map from north of new map
bool map_loaded_from_north = false;

// Checks if a map is currently loaded
bool is_map_loaded = false;

// Don't touch this variable unless you know what you are doing
// Used to scale window and sprites
int scale_factor = 2;
int getScaleFactor()
{
   return scale_factor;
}

// Function: checkCollision
// - checks if the direction the player wants to go has collision
// - returns true if there is collision, false otherwise
bool checkCollision(sf::Keyboard::Key input, Player& player, const Map& map)
{
   if (input == RIGHT_KEY)
   {
      // Check if collision exists for that tile type, > 0 means collision
      if (map.CollisionData[map.MapData[player.pos_Y][player.pos_X + 1]])
      {
         return true;
      }
   }
   else if (input == LEFT_KEY)
   {
      // Check if collision exists for that tile type, > 0 means collision
      if (map.CollisionData[map.MapData[player.pos_Y][player.pos_X - 1]])
      {
         return true;
      }
   }
   else if (input == UP_KEY)
   {
      // Check if collision exists for that tile type, > 0 means collision
      if (map.CollisionData[map.MapData[player.pos_Y - 1][player.pos_X]])
      {
         return true;
      }
   }
   else if (input == DOWN_KEY)
   {
      // Check if collision exists for that tile type, > 0 means collision
      if (map.CollisionData[map.MapData[player.pos_Y + 1][player.pos_X]])
      {
         return true;
      }
   }
   // Make sure player doesn't walk out of bounds
   //else if (0 < player.pos_X < map.map_width &&
   //         0 < player.pos_Y < map.map_height)
   //{
   //   return true;
   //}
   return false; // No collision
}

// Function: handleKeyPress
// - handles event where key is pressed (generally user input)
void handleKeyPress(sf::Keyboard::Key input, sf::RenderWindow& window, Player& player,
                    const std::vector<sf::Texture>& Textures, Map& CurrentMap,
                    Map& AdjacentMap, const sf::Texture& black_texture,
                    sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH])
{
   // Events that require updating the entire VisibleGrid
   if (input == LEFT_KEY || input == RIGHT_KEY
       || input == UP_KEY || input == DOWN_KEY)
   {
      // Check if movement in that direction is valid based on collisions
      if (!checkCollision(input, player, CurrentMap))
      {
         if (input == RIGHT_KEY)
         {
            // Increment players x-position in the map, we do this first..
            // ..to figure out what needs to be done where the player goes
            player.pos_X++;

            // Check if player is close enough to load adjacent map
            if (player.pos_X == CurrentMap.map_width - (TILES_TO_LOAD + 1)
                && !is_map_loaded && CurrentMap.east_map_source != "NA")
            {
               std::cout<<"Loading map"<<std::endl;
               is_map_loaded = true;
               map_loaded_from_west = true;

               AdjacentMap = loadMap(CurrentMap.east_map_source);
               std::swap(CurrentMap, AdjacentMap);
               player.pos_X = 0;
               // FIGURE OUT PLAYER Y POS
            }
            // Occurs if player turns back to old map during map transition
            if (player.pos_X > (CurrentMap.map_width - TILES_TO_LOAD) - 2
                && map_loaded_from_east)
            {
               // Store how far player was sitting in transition boundary
               int distance_from_border = CurrentMap.map_width - player.pos_X;
               std::swap(CurrentMap, AdjacentMap);
               player.pos_X = TILES_TO_LOAD - distance_from_border + 1;
               map_loaded_from_east = false;
               map_loaded_from_west = true;
            }
            // Unload map if far enough from border
            if (player.pos_X > TILES_TO_LOAD - 1 && map_loaded_from_west)
            {
               std::cout<<"Unloading map"<<std::endl;
               is_map_loaded = false;
               map_loaded_from_west = false;
               // Clear adjacent map?
            }
            translateVisibleGridRight(VisibleGrid, CurrentMap, Textures,
                                      player, black_texture);
         }


         else if (input == LEFT_KEY)
         {
            // Decrement players x-position in the map, we do this first..
            // ..to figure out what needs to be done where the player goes
            player.pos_X--;

            // Check if player is close enough to load adjacent map
            if (player.pos_X == TILES_TO_LOAD - 1 && !is_map_loaded)
            {
               // If this fails, player got too close to border on accident
               if (CurrentMap.west_map_source != "NA")
               {
                  std::cout<<"Loading map"<<std::endl;
                  is_map_loaded = true;
                  map_loaded_from_east = true;

                  AdjacentMap = loadMap(CurrentMap.west_map_source);
                  std::swap(CurrentMap, AdjacentMap);
                  player.pos_X = CurrentMap.map_width - 2;
                  // FIGURE OUT PLAYER Y POS
               }
            }
            // Occurs if player turns back to old map during map transition
            if (player.pos_X < TILES_TO_LOAD && map_loaded_from_west)
            {
               int distance_from_border = player.pos_X - 1;
               std::swap(CurrentMap, AdjacentMap);
               player.pos_X = (CurrentMap.map_width - TILES_TO_LOAD)
                               + distance_from_border;
               map_loaded_from_west = false;
               map_loaded_from_east = true;
            }
            // Unload map if far away from border
            if (player.pos_X < (CurrentMap.map_width - TILES_TO_LOAD) - 1
                && map_loaded_from_east)
            {
               std::cout<<"Unloading map"<<std::endl;
               is_map_loaded = false;
               map_loaded_from_east = false;
               // Clear adjacent map?
            }
            translateVisibleGridLeft(VisibleGrid, CurrentMap, Textures, player,
                                     black_texture);
         }


         else if (input == DOWN_KEY)
         {
            // Increment players y-position in the map, we do this first..
            // ..to figure out what needs to be done where the player goes
            player.pos_Y++;

            // Check if player is close enough to load adjacent map
            if (player.pos_Y == CurrentMap.map_height - TILES_TO_LOAD
                && !is_map_loaded)
            {
               // If this fails, player got too close to border on accident
               if (CurrentMap.south_map_source != "NA")
               {
                  std::cout<<"Loading map"<<std::endl;
                  is_map_loaded = true;
                  map_loaded_from_north = true;

                  AdjacentMap = loadMap(CurrentMap.west_map_source);
                  std::swap(CurrentMap, AdjacentMap);
                  player.pos_Y = 0;
                  // FIGURE OUT PLAYER X POS
               }

            }
            //if (player.pos_Y > TILES_TO_LOAD - 1 && is_north_map_loaded)
            //{
            //   is_north_map_loaded = false;
            //   std::cout<<"Unloading map"<<std::endl;
            //}
            translateVisibleGridDown(VisibleGrid, CurrentMap, Textures,
                                     player, black_texture);
         }


         else if (input == UP_KEY)
         {
            // Decrement players y-position in the map, we do this first..
            // ..to figure out what needs to be done where the player goes
            player.pos_Y--;

            // Check if player is close enough to load adjacent map
            if (player.pos_Y == TILES_TO_LOAD - 1 && !is_map_loaded)
            {
               // If this fails, player got too close to border on accident
               if (CurrentMap.north_map_source != "NA")
               {
                  std::cout<<"Loading map"<<std::endl;
                  is_map_loaded = true;
                  map_loaded_from_south = true;

                  AdjacentMap = loadMap(CurrentMap.west_map_source);
                  std::swap(CurrentMap, AdjacentMap);
                  player.pos_Y = CurrentMap.map_height - 1;
                  // FIGURE OUT PLAYER X POS
               }
            }
            //if (player.pos_Y < CurrentMap.map_height - TILES_TO_LOAD
            //         && is_south_map_loaded)
            //{
            //   is_south_map_loaded = false;
            //   std::cout<<"Unloading map"<<std::endl;
            //}
            translateVisibleGridUp(VisibleGrid, CurrentMap, Textures, player,
                                   black_texture);
         }
         std::cout<<"Player pos x: "<<player.pos_X<<std::endl;
         drawVisibleGrid(VisibleGrid, window, player);
      } // Done checking movement keys
   }// Done checking for collision

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
   Map AdjacentMap; // Will load adjacent maps to CurrentMap here

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
   player.pos_X = 6;
   player.pos_Y = 8;
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
            handleKeyPress(event.key.code, window, player, Textures,
                           CurrentMap, AdjacentMap, black_texture, VisibleGrid);
         }
      } // End of event poll
   } // End of game loop

   return EXIT_SUCCESS;
}
