// Bruce Smith
// 2024-11-27
//
// Contains main

#include <iostream> // For IO debugging
#include <SFML/Graphics.hpp> // For window/rendering calls
#include "Project-Libraries/resize_window.h"

const int VISIBLE_WIDTH = 10;   // 10 tiles wide
const int VISIBLE_HEIGHT = 9;   // 9 tiles tall

const int DEFAULT_WINDOW_WIDTH = 160;   // 160 pixels wide
const int DEFAULT_WINDOW_HEIGHT = 144;   // 144 pixels tall

const int TILE_SIZE = 16;   // Defualt tile size of 16 pixels

// Function: initializeVisibleGrid
// - initalizes a grid of textures that will be displayed to the window
int initializeVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH], sf::Texture& texture)
{
   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         VisibleGrid[y][x].setTexture(texture);
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
   sf::Sprite VisibleGrid[VISIBLE_HEIGHT][VISIBLE_WIDTH];

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
            // Only update screen when arrow keys are pressed
            window.clear();

            for (int y = 0; y < VISIBLE_HEIGHT; y++)
            {
               for (int x = 0; x < VISIBLE_WIDTH; x++)
               {
                  window.draw(VisibleGrid[y][x]);
               }
            }

            window.display();
         }
      }
   }

   return EXIT_SUCCESS;
}
