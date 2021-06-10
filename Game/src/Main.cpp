#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace sf;
int main()
{
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(1024, 768), "Flappy Bird!");
	window.setFramerateLimit(60);

	//Background
	Texture background;
	background.loadFromFile("sprites/background-day.png");
	Sprite BG(background);
	BG.setPosition(0, 0);

	//Bird
	Texture bird_still, bird_up, bird_down;
	bird_still.loadFromFile("sprites/bluebird-midflap.png");
	bird_up.loadFromFile("sprites/bluebird-upflap.png");
	bird_down.loadFromFile("sprites/bluebird-downflap.png");
	Sprite Bird(bird_still);
	Bird.setPosition(300.f, 400.f);


	//Sounds
	Sound sound;
	SoundBuffer wing;
	SoundBuffer swoosh;
	SoundBuffer die;
	SoundBuffer hit;
	wing.loadFromFile("audio/wing.ogg");
	swoosh.loadFromFile("audio/swoosh.ogg");
	die.loadFromFile("audio/die.ogg");
	hit.loadFromFile("audio/hit.ogg");
	
	
	//Score
	float currentscore = 1;
	Font myFont;
	myFont.loadFromFile("font/flappybird.ttf");
	Text score;
	score.setFont(myFont);
	score.setFillColor(Color::Black);
	score.setStyle(Text::Bold);
	score.setString("Score");
	score.setCharacterSize(75);
	score.setPosition(0, -25);
	Texture number;
	number.loadFromFile("sprites/0.png");
	Sprite zero(number);
	Texture number1;
	number1.loadFromFile("sprites/1.png");
	Sprite one(number1);
	Texture number2;
	number2.loadFromFile("sprites/2.png");
	Sprite two(number2);
	Texture number3;
	number3.loadFromFile("sprites/3.png");
	Sprite three(number3);
	Texture number4;
	number4.loadFromFile("sprites/4.png");
	Sprite four(number4);
	Texture number5;
	number5.loadFromFile("sprites/5.png");
	Sprite five(number5); 
	Texture number6;
	number6.loadFromFile("sprites/6.png");
	Sprite six(number6);
	Texture number7;
	number7.loadFromFile("sprites/7.png");
	Sprite seven(number7);
	Texture number8;
	number8.loadFromFile("sprites/8.png");
	Sprite eight(number8);
	Texture number9;
	number9.loadFromFile("sprites/9.png");
	Sprite nine(number9);
	map<int, Sprite>m;
	m[0] = zero;
	m[1] = one;
	m[2] = two;
	m[3] = three;
	m[4] = four;
	m[5] = five;
	m[6] = six;
	m[7] = seven;
	m[8] = eight;
	m[9] = nine;
	for (int i = 0; i < 10; i++)
	{
		m[i].setPosition(0, 50);
	}


	//Pipes
	Texture pipe;
	pipe.loadFromFile("sprites/pipe-green.png");
	Sprite Pipe_down(pipe);
	Sprite Pipe_up(pipe);
	Pipe_up.rotate(180);
	Pipe_down.setPosition(700, 448);
	Pipe_up.setPosition(400, 320);
	

	
	//Speeds
	float Bird_speed = 1;
	float gravity = 1;

	//View
	View view1(FloatRect(0.f, 0.f, 1024.f, 768.f));
	view1.setCenter(512, 384);

	//Pipes vector
	vector<Sprite> pipes;
	pipes.push_back(Pipe_up);
	pipes.push_back(Pipe_down);

	//SpawnTimer
	int PipeSpawnTimer = 20;

	int l = 0;
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
					sound.setBuffer(wing);
					sound.play();
					Bird.move(Bird_speed, -50+gravity);
				}
				else if (event.key.code == Keyboard::Down)
				{
					Bird.setTexture(bird_down);
					sound.setBuffer(swoosh);
					sound.play();
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
		if (Bird.getPosition().y < 0.f)
			Bird.setPosition(Bird.getPosition().x, 0.f);

		if (Bird.getPosition().y < 10.f)
			Bird.setPosition(Bird.getPosition().x, 10.f);

		if (Bird.getPosition().y >= 750.f)
			Bird.setPosition(Bird.getPosition().x, 750.f);

		if (PipeSpawnTimer < 300)
			PipeSpawnTimer++;

		if (PipeSpawnTimer >= 300)
		{
			if (rand() % 2 == 0)
			{
				Sprite pup(pipe);
				pup.rotate(180);
				pup.setPosition(730 + Bird.getPosition().x, 300 - (rand() % 150));
				pipes.push_back(pup);
			}
			else
			{
				Sprite pd(pipe);
				pd.setPosition(730 + Bird.getPosition().x, 350 + (rand() % 150));
				pipes.push_back(pd);
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
			if (Bird.getPosition().x-pipes[i].getPosition().x>500)
			{
				pipes.erase(pipes.begin() + i);
				std::cout << "Erased pipes[" << i << "]" << std::endl;
			}
		}

		int n = currentscore;
		window.clear();

		window.draw(BG);
		window.draw(Bird);
		for (int i = 0; i < pipes.size(); i++)
		{
			window.draw(pipes[i]);
		}
		window.draw(score);
		vector <int> temp;
		while (n > 0)
		{
			temp.push_back(n % 10);
			n = n / 10;
		}
		l = temp.size();
		for (int i = l-1; i>=0; i--)
		{
			m[temp[i]].setPosition(BG.getPosition().x + 24*(l-1-i),50);
			window.draw(m[temp[i]]);
		}
		window.display();
		for (int i = 0; i != pipes.size(); i++)
		{
			window.draw(pipes[i]);
		}
		Bird.move(Bird_speed, gravity);
		view1.move(Bird_speed, 0);
		score.move(Bird_speed, 0);
		BG.move(Bird_speed, 0);
		currentscore=currentscore+0.1;

	}

	return 0;
}