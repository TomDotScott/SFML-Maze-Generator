#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>

#include "constants.h"

int random_range(const int min, const int max)
{
	static bool first = true;
	if (first)
	{
		//seeding for the first time only!
		srand(static_cast<unsigned>(time(nullptr)));
		first = false;
	}
	return min + rand() % ((max)-min);
}

template <typename T>
bool is_item_in_vector(std::vector<T>& vec, const T value)
{
	return std::find(vec.begin(), vec.end(), value) != vec.end();
}

template<typename T>
int index_of_item(const std::vector<T>& vec, T value)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == value)
		{
			return i;
		}
	}
	return -1;
}

void render(std::vector<std::pair<int, int>>& maze, sf::RenderWindow& window)
{
	window.clear();
	sf::RectangleShape border{ {constants::k_screenWidth - 6, constants::k_screenHeight - 6} };
	border.setPosition(3, 3);
	border.setFillColor(sf::Color::Black);
	border.setOutlineThickness(3);
	window.draw(border);

	// Draw the maze
	for (int y = 0; y < constants::k_mazeHeight; ++y)
	{
		for (int x = 0; x < constants::k_mazeWidth; ++x)
		{
			// only worry about the tile to the right and the tile below
			// to avoid drawing lines twice
			const int current{ y * constants::k_mazeWidth + x };
			const int lower{ (y + 1) * constants::k_mazeWidth + x };

			// if the maze doesn't contain the path, draw a wall
			if(!is_item_in_vector(maze, std::pair<int, int>(current, lower)))
			{
				sf::Vertex line[]
				{
					sf::Vertex({static_cast<float>(x * constants::k_tileWidth), static_cast<float>((y + 1) * constants::k_tileHeight)}),
					sf::Vertex({static_cast<float>((x + 1) * constants::k_tileWidth), static_cast<float>((y + 1) * constants::k_tileHeight)})
				};
				window.draw(line, 2, sf::Lines);
			}

			if(!is_item_in_vector(maze, std::pair<int, int>(current, current + 1)))
			{
				sf::Vertex line[]
				{
					sf::Vertex({static_cast<float>((x + 1) * constants::k_tileWidth), static_cast<float>(y * constants::k_tileHeight)}),
					sf::Vertex({static_cast<float>((x + 1) * constants::k_tileWidth), static_cast<float>((y + 1) * constants::k_tileHeight)})
				};
				window.draw(line, 2, sf::Lines);
			}
		}
	}

	window.display();
}

void prims_algorithm(std::vector<std::pair<int, int>>& maze, sf::RenderWindow& window)
{
	std::vector<int> visitedIndices{ 0 };

	// The cache of paths in the maze that we are building up
	// For instance, (0, 1) means a path FROM 0 TO 1
	// We are starting with the top left corner and the cell directly below it...
	// This does not mean that this will be the path, it is just a POSSIBLE path
	// for us to take
	std::vector<std::pair<int, int>> nodesToVisit{
		std::pair<int, int>(0, 1),
		std::pair<int, int>(0, constants::k_mazeWidth)
	};

	// We want to keep looping whilst there are nodes on our "graph" to visit
	while (!nodesToVisit.empty())
	{
		const auto randomIndex = random_range(0, static_cast<int>(nodesToVisit.size()));
		const auto nextPath    = nodesToVisit[randomIndex];

		// Remove the item from the nodesToVisit vector
		const auto indexToRemove = index_of_item(nodesToVisit, nextPath);
		if (indexToRemove != -1)
		{
			nodesToVisit.erase(nodesToVisit.begin() + index_of_item(nodesToVisit, nextPath));
		}

		// If the item is in the visited list then we don't continue the logic
		if (!is_item_in_vector(visitedIndices, nextPath.second))
		{
			// add the node to the visited list
			visitedIndices.push_back(nextPath.second);

			// if the path is from right to left, or bottom to top, flip it
			if(nextPath.first > nextPath.second)
			{
				maze.emplace_back(nextPath.second, nextPath.first);
			} else
			{
				// add the node to the maze
				maze.emplace_back(nextPath);
			}
			
			// Find the index of the cell above the current cell
			const auto above = nextPath.second - constants::k_mazeWidth;
			// make sure the above is valid
			if (above > 0 && !is_item_in_vector(visitedIndices, above))
			{
				nodesToVisit.emplace_back(nextPath.second, above);
			}

			const auto left = nextPath.second - 1;
			if (left % constants::k_mazeWidth != constants::k_mazeWidth - 1 && !is_item_in_vector(visitedIndices, left))
			{
				nodesToVisit.emplace_back(nextPath.second, left);
			}

			const auto right = nextPath.second + 1;
			if (right % constants::k_mazeWidth != 0 && !is_item_in_vector(visitedIndices, right))
			{
				nodesToVisit.emplace_back(nextPath.second, right);
			}

			const auto below = nextPath.second + constants::k_mazeWidth;
			if (below < constants::k_mazeHeight * constants::k_mazeWidth && !is_item_in_vector(visitedIndices, below))
			{
				nodesToVisit.emplace_back(nextPath.second, below);
			}
		}
	}

	for(size_t i = 0; i < maze.size(); ++i)
	{
		auto currentMazeState = std::vector<std::pair<int, int>>(maze.begin(), maze.begin() + i);
		render(currentMazeState, window);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(constants::k_screenWidth, constants::k_screenHeight), "Maze Generator: Prim's Algorithm");
	std::vector<std::pair<int, int>> maze;
	prims_algorithm(maze, window);
	while (window.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event{};
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

		render(maze, window);


		// Get the window to display its contents
		window.display();
	}

	return 0;
}
