#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>



class Renderer
{
public:
	Renderer();
	void Draw();
	void TestLoop();

private:
	sf::RenderWindow window;
};
