#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
    RenderWindow window(sf::VideoMode(288, 512), "SFML works!");
    Texture background;
    background.loadFromFile("sprites/background-day.png");
    Sprite BG(background);

    Texture bird_still,bird_up,bird_down;
    bird_still.loadFromFile("sprites/bluebird-midflap.png");
    bird_up.loadFromFile("sprites/bluebird-upflap.png");
    bird_down.loadFromFile("sprites/bluebird-downflap.png");
    Sprite Bird(bird_still);
    Bird.setPosition(288 / 2, 512 / 2);

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
                }
                else if (event.key.code == Keyboard::Down)
                {
                    Bird.setTexture(bird_down);
                }
            }
            else
            {
                Bird.setTexture(bird_still);
            }
        }
        window.clear();
        window.draw(BG);
        window.draw(Bird);
        window.display();
    }

    return 0;
}