// project_gamebuoy.cpp
// Bruce Smith
// 2024-11-29
//
// Contains main
// Check constants.h for more information on constant variables

#include <iostream> // For IO debugging
#include <SFML/Graphics.hpp>   // For window/rendering calls
#include "Project-Libraries/resize_window.h"   // Handles resizing screen
#include "Project-Libraries/mapLoader.h"   // Handles loading and unloading map data
#include "Project-Libraries/constants.h"   // Access to commonly used variables

// Function: drawVisibleGrid
void drawVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                     sf::RenderWindow& window)
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
   window.display();
}

// Function: handleKeyPress
// - handles event where key is pressed (generally user input)
void handleKeyPress(sf::Keyboard::Key input, sf::RenderWindow &window,
                    sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH])
{
   // Events that require updating the entire VisibleGrid
   if (input == LEFT_KEY || input == RIGHT_KEY
       || input == UP_KEY || input == DOWN_KEY)
   {
      drawVisibleGrid(VisibleGrid, window);
   }

   // Events that require resizing the screen
   else if (input == NUM1_KEY || input == NUM2_KEY || input == NUM3_KEY)
   {
      // Scale factor of the screen and tiles
      unsigned int scale_factor = 1;

      if (input == NUM1_KEY)      scale_factor = 1;
      else if (input == NUM2_KEY) scale_factor = 2;
      else if (input == NUM3_KEY) scale_factor = 3;
      resizeWindow(window, scale_factor, VisibleGrid);
   }
}

// Function: initializeVisibleGrid
// - initalizes a grid of textures that will be displayed to the window
int initializeVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                          sf::Texture& texture)
{
   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         VisibleGrid[y][x].setTexture(texture); // Applies missing_texture for now
         VisibleGrid[y][x].setPosition(x * TILE_SIZE, y * TILE_SIZE);
      }
   }

   return 0;
}

int main()
{
   sf::Texture missing_texture;
   if (!missing_texture.loadFromFile("Assets/missing_texture.png"))
   {
      return EXIT_FAILURE;
   }
   missing_texture.setSmooth(false);   // Disable smooth filter

   // Create grid that will be displayed to the window
   // NOTE: SHOULD ONLY CONTAIN GAME TERRAIN, NOT MENUS
   sf::Sprite VisibleGrid[VISIBLE_HEIGHT][VISIBLE_WIDTH];

   // Initialize VisibleGrid with missing_texture
   initializeVisibleGrid(VisibleGrid, missing_texture);

   // Create main window
   sf::RenderWindow window(sf::VideoMode(DEFAULT_WINDOW_WIDTH,
                                         DEFAULT_WINDOW_HEIGHT), "GameBuoy");

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
            handleKeyPress(event.key.code, window, VisibleGrid);
         }
      } // End of event poll
   } // End of game loop

   return EXIT_SUCCESS;
}
