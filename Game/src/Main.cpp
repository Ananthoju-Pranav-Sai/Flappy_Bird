#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
    RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    Texture texture;
    texture.loadFromFile("sprites/char.png");
    Sprite sprite(texture);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}