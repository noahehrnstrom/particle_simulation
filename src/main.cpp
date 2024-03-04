#include <vector>
#include <iostream>
#include <cmath>
#include <omp.h>
#include "../include/helper.hpp"

sf::Clock ctr;

bool mpressed, rpressed;

sf::Vector2i mpos;

void update(std::vector<sf::Vector2f> &pos, std::vector<sf::Vector2f> &vel, std::vector<sf::Color> &cs)
{
    for (size_t i = 0; i < pos.size(); i++) {
        sf::Vector2f dif = pos[i] - sf::Vector2f(mpos);
        sf::Vector2f normalised = normalise(dif);
        if(mpressed) {
            vel[i] -= sf::Vector2f(normalised.x / 5, normalised.y / 5);
        }
        if(rpressed) {
            vel[i] += sf::Vector2f(normalised.x / 5, normalised.y / 5);
        }

        float curdif = abs(vel[i].x) + abs(vel[i].y) + ((sin(ctr.getElapsedTime().asMilliseconds() / 300) * 1.5) + 1.5);

        cs[i].b = 255;

        cs[i].r = 255 * (int)(curdif * 20 > 255) + curdif * 20 * (int)(curdif * 20 <= 255);

        vel[i].x *= 0.99;
        vel[i].y *= 0.99;
        pos[i] += sf::Vector2f(vel[i].x * 3, vel[i].y * 3);
    }
}

int main()
{
    const unsigned int size = 150000;

    std::vector<sf::Vector2f> pos;
    std::vector<sf::Vector2f> vel;
    std::vector<sf::Color> cs;

    float zoom;

    sf::RectangleShape p;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "particles", sf::Style::Fullscreen);

    window.setMouseCursorVisible(false);

    int x = window.getSize().x, y = window.getSize().y;
    for (unsigned int i = 0; i < size; i++)
    {
        pos.push_back(sf::Vector2f(genRandomInt(0, x), genRandomInt(0, y)));
        vel.push_back(sf::Vector2f(0, 0));
        cs.push_back(sf::Color::Blue);
    }

    zoom = 1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved)
            {
                mpos = sf::Mouse::getPosition(window);
                mpos = sf::Vector2i((mpos.x / zoom), (mpos.y / zoom));
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                zoom += event.mouseWheel.delta * 0.01;
                mpos = sf::Mouse::getPosition(window);
                mpos = sf::Vector2i((mpos.x / zoom), (mpos.y / zoom));
            }
        }

        window.clear(sf::Color::Black);

        rpressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
        mpressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        update(pos, vel, cs);

        p.setSize(sf::Vector2f(zoom * 1, zoom * 1));
        p.setFillColor(sf::Color::Yellow);
        for (size_t i = 0; i < pos.size(); i++)
        {
            p.setFillColor(cs[i]);
            p.setPosition(pos[i].x * zoom, pos[i].y * zoom);
            window.draw(p);
        }
        p.setSize(sf::Vector2f(4, 4));
        p.setFillColor(sf::Color(255, 0, 255));
        p.setPosition(mpos.x * zoom, mpos.y * zoom);
        window.draw(p);

        window.display();
    }
    return 0;
}
