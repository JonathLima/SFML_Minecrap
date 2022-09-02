#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>


int main()
{
	std::srand(std::time(nullptr));

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Minecrap - v0.1");
	window.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("Textures/minecrap.png");
	sf::Sprite object(texture);

	float x = static_cast<float>(std::rand() % static_cast<int>(window.getSize().x - texture.getSize().x - 10));
	object.setPosition(sf::Vector2f(x, 10.f));

	int points{}, health{ 3 };

	std::vector<sf::Sprite> objs;
	size_t max_objs{ 5 };
	float obj_vel_max{ 10.f };
	float obj_vel = obj_vel_max;

	sf::Vector2i pos_mouse_win;
	sf::Vector2f pos_mouse_coord;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

			pos_mouse_win = sf::Mouse::getPosition(window);
			pos_mouse_coord = window.mapPixelToCoords(pos_mouse_win);

		}

		if (objs.size() < max_objs)
		{
			if (obj_vel >= obj_vel_max)
			{
				x = static_cast<float>(std::rand() % static_cast<int>(window.getSize().x - texture.getSize().x - 10));
				object.setPosition(x, 0.f);
				objs.push_back(object);
				obj_vel = 0.f;
			}
			else
			{
				obj_vel += 1.f;
			}
		}

		for (size_t i{}; i < objs.size(); ++i)
		{
			bool del = false;
			objs[i].move(0, 5.f);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (objs[i].getGlobalBounds().contains(pos_mouse_coord))
				{
					del = true;
					points += 10;
				}
			}
			if (objs[i].getPosition().y > window.getSize().y)
			{
				--health;
				del = true;
				if (health <= 0)
				{
					window.close();
				}
			}
			if (del)
			{
				objs.erase(objs.begin() + i);
			}
		}




		window.clear();
		for (auto& e : objs)
		{
			window.draw(e);
		}
		window.display();
	}

	return EXIT_SUCCESS;
}