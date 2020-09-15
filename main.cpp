#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include <math.h>

#include <iostream>

#define windowWidth 1024
#define windowHeight 800

using namespace std;

/*Hello test */

int sign(float num){
    if(num<0) return -1;
    if(num>0) return 1;
    return 0;
};

sf::SoundBuffer buffer;
sf::Sound sound;


class Player{
public:

    float x;
    float y;
    float maxSpeed = 0.04;
    float maxSpeedJump = -0.08;
    float ballR = 30.f;
    float startX = windowWidth/2;
    float startY = windowHeight-ballR*2;

    int bounceCount=0;

    float floorC = startY;

    float speedY =0;
    float gravity = 0.00001;
    bool inJump = false;

    float speed=0;
    float acc = 0.00001;

    sf::Color color = sf::Color::Green;

    /*update position itself*/
    void setColor(){
        if(y==startY && !inJump) {
            color = sf::Color::Red;
        }else{
                color = sf::Color::Green;
        }

    }
    void updatePos() {
        if (speed > maxSpeed) speed = maxSpeed;
        if (speed < -maxSpeed) speed = -maxSpeed;

        speed = (speed / 1.0001);
        speedY +=gravity;

        //if(abs(speed)<0.000009) speed=0;

        //speed = (abs(speed) - acc)*sign(speed) ;
        wallColl();
        y += speedY;
        x += speed;

        if(speedY==0){
            inJump=false;
        }
    }
    void jump(){
        if(y==startY && !inJump) {
            speedY = maxSpeedJump;
            inJump=true;
            sound.play();
          //  soundBounce();
        }
    }

private:
    void wallColl(){
        if(x+speed<=0) speed*=-0.8;


        if(x+speed>=windowWidth-(ballR*2)) speed*=-0.8;

        if(speedY>0){
        if(y+speedY>floorC){
                speedY=-speedY*0.5;

        }
        else inJump=false;
        }



    }


};

void ControllHandler(Player &ball){

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

        cout<< "\n X= "<< ball.speed;
        cout<< "\n Y= "<< ball.speedY;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        ball.x = ball.startX;
        ball.speed=0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) ball.y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ball.speed+=ball.acc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ball.speed-=ball.acc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        ball.jump();
    }

}


int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Jumper", sf::Style::Close);



    if (!buffer.loadFromFile("sound/bounce.ogg"))
        cout <<"error";

    sound.setBuffer(buffer);


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



        ControllHandler(ball);
        ball.updatePos();
        ball.setColor();
        shape.setFillColor(ball.color);

        shape.setPosition(ball.x,ball.y);


        window.clear();
        window.draw(shape);

        window.display();
    }

    return 0;
}

