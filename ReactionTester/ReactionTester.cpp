#include "pch.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>

//dimensions for window size and background
int num_vertBox = 95, num_horzBox = 90;

int size = 10;
int w = size * num_horzBox; //background number of pixels in width
int h = size * num_vertBox; //background number of pixels in height

sf::CircleShape target(100.f);

//Array that holds the different colors for circle
sf::Color colors[5] = {sf::Color::Cyan, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Yellow};

//Target spawns at random locations
void spawn() {

	//Spawn a circle with a random color from the array
	target.setFillColor(colors[rand() % 5]);

	target.setPosition(rand() % (w - 100), rand() % (h - 100));

}

int main() {

	sf::Font font;

	//load in the font to use
	if (!font.loadFromFile("rm_typerighter_medium.ttf")) {
		std::cout << "Error loading file" << std::endl;
		system("pause");
	}

	sf::Text text;

	text.setFont(font);

	text.setCharacterSize(50);

	std::stringstream ss;

	sf::RenderWindow window(sf::VideoMode(w, h), "Reaction Tester");
	
	target.setFillColor(sf::Color::Red);

	//initial starting position
	target.setPosition(450, 475);

	sf::Clock clock;

	while (window.isOpen()) {

		sf::Event e;

		while (window.pollEvent(e)) {
			
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && target.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {

					sf::Time elapsed = clock.getElapsedTime();
					ss.str(std::string());
					ss << "Elapsed time: ";
					ss << elapsed.asSeconds();

					text.setString(ss.str().c_str());

					clock.restart();
					spawn();
						
				}
				break;
			}
		}

		window.clear();
		window.draw(text);
		window.draw(target);
	
		window.display();
	}
}