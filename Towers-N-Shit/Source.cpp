#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include "Tile.h"
#include "Level.h"

using namespace std;

int main(){
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!"); //create 720p window, using 720p until i scale up to 1080p
	sf::Font font;
	sf::Text fpscounter;
	sf::Clock clk;
	sf::RectangleShape rekt(sf::Vector2f(32, 32));

	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(0);

	if (!font.loadFromFile("cour.ttf")) {
		cout << "Error loading font.." << endl;
		while (1);
	}
	fpscounter.setFont(font);
	fpscounter.setCharacterSize(18);
	fpscounter.setPosition(sf::Vector2f(10, 10));
	fpscounter.setColor(sf::Color::White);

	Tile tiles[32][32]; //load grid for turrets

	clk.restart();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //exit on button close event
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape) //exit on esc key event
					window.close();
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left){
					int mousex = event.mouseButton.x, mousey = event.mouseButton.y;
					if (mousex / 32 < 32 && mousex >= 0 && mousey / 32 < 32 && mousey >= 0) {
						if (!tiles[mousex / 32][mousey / 32].getOccupied()) {
							tiles[mousex / 32][mousey / 32].toggle();
							cout << mousex / 32 << ", " << mousey / 32 << endl;
						}
					}
				}
		}
		sf::Vector2i mousepos = sf::Mouse::getPosition(window);
		window.clear();
		rekt.setPosition((float)mousepos.x - (mousepos.x % 32), (float)mousepos.y - (mousepos.y % 32));
		if ((mousepos.x / 32) < 32 && mousepos.x >= 0 && (mousepos.y / 32) < 32 && mousepos.y >= 0) {
			if (tiles[mousepos.x / 32][mousepos.y / 32].getOccupied()) {
				rekt.setFillColor(sf::Color(255, 0, 0, 50));
				window.draw(rekt);
			}
			else {
				rekt.setFillColor(sf::Color(0, 255, 0, 50));
				window.draw(rekt);
			}
		}
		window.draw(fpscounter);
		window.display();
		fpscounter.setString("FPS: " + to_string((int)(1000000.0f / clk.getElapsedTime().asMicroseconds())));
		clk.restart();
	}

	return 0;
}