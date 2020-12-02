#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(constants::k_screenWidth, constants::k_screenHeight), "Maze Generator: Prim's Algorithm");
	
	while (window.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		// We must clear the window each time around the loop
		window.clear();



		// Get the window to display its contents
		window.display();
	}

	return 0;
}
