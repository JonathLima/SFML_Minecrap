#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Minecrap - v0.1");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		
		}

		window.clear();
		//window.draw(ball);
		window.display();
	}

	return EXIT_SUCCESS;
}