#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include <fstream>
#include "Tile.h"
#include "Level.h"
#include "Enemy.h"

using namespace std;

int main(){
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::Close); //create 720p window, using 720p until i scale up to 1080p (if!!? Maybe just play game at 720p and upscale)
	sf::Font font;
	sf::Text fpscounter;
	sf::Clock clk;
	sf::Sprite background;
	sf::Texture bg_pic;

	if (!bg_pic.loadFromFile("level1.png")) 
		while (1);
	background.setTexture(bg_pic);
	sf::RectangleShape rekt(sf::Vector2f(32, 32));

	Tile tiles[40][20]; //load grid for turrets

	fstream input;
	input.open("level1.dat", fstream::in);
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 20; j++) {
			char inp = input.get();
			cout << inp << " ";
			if (inp == '1') tiles[i][j].toggle();
		}
	}
	input.close();

	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(0);

	if (!font.loadFromFile("cour.ttf")) 
		while (1);
	fpscounter.setFont(font);
	fpscounter.setCharacterSize(18);
	fpscounter.setPosition(sf::Vector2f(10, 10));
	fpscounter.setColor(sf::Color::White);

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
				if (event.mouseButton.button == sf::Mouse::Left) {
					int mousex = event.mouseButton.x, mousey = event.mouseButton.y;
					if (mousex / 32 < 40 && mousex >= 0 && mousey / 32 < 20 && mousey >= 0) {
						if (!tiles[mousex / 32][mousey / 32].getOccupied()) {
							tiles[mousex / 32][mousey / 32].toggle();
							cout << mousex / 32 << ", " << mousey / 32 << endl;
						}
					}
				}
		}
		sf::Vector2i mousepos = sf::Mouse::getPosition(window);
		window.clear();
		window.draw(background);
		rekt.setPosition((float)mousepos.x - (mousepos.x % 32), (float)mousepos.y - (mousepos.y % 32));
		if ((mousepos.x / 32) < 40 && mousepos.x >= 0 && (mousepos.y / 32) < 20 && mousepos.y >= 0) {
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