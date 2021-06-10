#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(1024, 800), "Flappy Bird!");
	window.setFramerateLimit(60);
	Texture background;
	background.loadFromFile("sprites/background-day.png");
	Sprite BG(background);

	Texture bird_still, bird_up, bird_down;
	bird_still.loadFromFile("sprites/bluebird-midflap.png");
	bird_up.loadFromFile("sprites/bluebird-upflap.png");
	bird_down.loadFromFile("sprites/bluebird-downflap.png");
	Sprite Bird(bird_still);
	Bird.setPosition(100.f, 400.f);
	float Bird_speed = 1;
	float gravity = 1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					Bird.setTexture(bird_up);
					Bird.move(Bird_speed, -50+gravity);
				}
				else if (event.key.code == Keyboard::Down)
				{
					Bird.setTexture(bird_down);
					Bird.move(Bird_speed, 50+gravity);
				}
			}
			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Down)
				{
					Bird.setTexture(bird_still);
				}
			}

		}
		if (Bird.getPosition().y < 10.f)
			Bird.setPosition(Bird.getPosition().x, 10.f);

		if (Bird.getPosition().y >= 700.f)
			Bird.setPosition(Bird.getPosition().x, 400.f);
		window.clear();
		window.draw(BG);
		window.draw(Bird);
		window.display();
		Bird.move(Bird_speed, gravity);
	}

	return 0;
}