#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <iostream>

#define windowWidth 1024
#define windowHeight 800

using namespace std;

/*Hello test */

class Player{
public:

    float x;
    float y;

    float ballR = 30.f;
    float startX = windowWidth/2;
    float startY = windowHeight-ballR*2;

    float speed = 0.04;

};


int main()
{
    //sf::Window window;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Jumper", sf::Style::Close);
   // sf::Window window(sf::VideoMode(800, 600), "My window");
    sf::CircleShape shape(30.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(windowWidth/2,windowHeight-60);
    Player ball;
    ball.x = ball.startX;
    ball.y = ball.startY;

    while (window.isOpen())
    {
        sf::Event event;


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            ball.x+=ball.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            ball.x-=ball.speed;
        }

        shape.setPosition(ball.x,ball.y);
        window.clear();
        window.draw(shape);

        window.display();
    }

    return 0;
}

