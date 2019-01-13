#include "../Headers/Renderer.h"

Renderer::Renderer()
{
	window.create(sf::VideoMode(1280, 640), "Gameboy");
}

void Renderer::Draw()
{
	//Draw the sprite
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(100, 100));
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(600, 300);

	window.draw(rectangle);
}

void Renderer::TestLoop()
{
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

		window.clear(sf::Color::Black);
		Draw();
		window.display();
	}
}
