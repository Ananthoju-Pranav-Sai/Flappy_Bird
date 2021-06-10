#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace sf;
int main()
{
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(1024, 768), "Flappy Bird!");
	window.setFramerateLimit(60);
	Texture background;
	background.loadFromFile("sprites/background-day.png");
	Sprite BG(background);
	BG.setPosition(0, 0);
	Texture bird_still, bird_up, bird_down;
	bird_still.loadFromFile("sprites/bluebird-midflap.png");
	bird_up.loadFromFile("sprites/bluebird-upflap.png");
	bird_down.loadFromFile("sprites/bluebird-downflap.png");

	Texture pipe;
	pipe.loadFromFile("sprites/pipe-green.png");

	Sprite Pipe_down(pipe);
	Sprite Pipe_up(pipe);
	Pipe_up.rotate(180);
	Pipe_down.setPosition(700, 448);
	Pipe_up.setPosition(400, 320);
	Sprite Bird(bird_still);

	Bird.setPosition(300.f, 400.f);

	float Bird_speed = 1;
	float gravity = 1;

	View view1(FloatRect(0.f, 0.f, 1024.f, 768.f));
	view1.setCenter(512, 384);

	//Pipes vector
	std::vector<sf::Sprite> pipes;
	pipes.push_back(Pipe_up);
	pipes.push_back(Pipe_down);

	//SpawnTimer
	int PipeSpawnTimer = 20;

	while (window.isOpen())
	{
		window.setView(view1);
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
					Bird.move(Bird_speed, -50 + gravity);
				}
				else if (event.key.code == Keyboard::Down)
				{
					Bird.setTexture(bird_down);
					Bird.move(Bird_speed, 50 + gravity);
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

		if (PipeSpawnTimer < 300)
			PipeSpawnTimer++;

		if (PipeSpawnTimer >= 300)
		{
			switch (rand() % 2)
			{
			case 0:
				Pipe_up.setPosition(730 + Bird.getPosition().x, 300 - (rand() % 150));
				pipes.push_back(Pipe_up);

			case 1:
				Pipe_down.setPosition(730 + Bird.getPosition().x, 350 + (rand() % 150));
				pipes.push_back(Pipe_down);
			}
			PipeSpawnTimer = 0;
			for (int i = 0; i < pipes.size(); i++)
			{
				std::cout << pipes[i].getPosition().x << std::endl;
			}
			std::cout << view1.getCenter().x -512 << std::endl;
			std::cout << std::endl;
		}
		for (int i = 0; i != pipes.size(); i++)
		{
			if (pipes[i].getPosition().x + 50 < view1.getCenter().x - 512)
			{
				pipes.erase(pipes.begin() + i);
				std::cout << "Erased pipes[" << i << "]" << std::endl;
			}
		}

		window.clear();

		window.draw(BG);
		window.draw(Bird);
		for (int i = 0; i != pipes.size(); i++)
		{
			window.draw(pipes[i]);
		}
		Bird.move(Bird_speed, gravity);
		view1.move(Bird_speed, 0);
		BG.move(Bird_speed, 0);

		window.display();
	}

	return 0;
}