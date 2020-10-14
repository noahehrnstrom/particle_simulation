#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>

std::random_device rng;
std::mt19937_64 dev(rng());

std::vector<sf::Vector2f> pos;
std::vector<sf::Vector2f> vel;
std::vector<sf::Color> cs;

float size = 15000;

sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "particles", sf::Style::Fullscreen);
//sf::RenderWindow window(sf::VideoMode(2000, 1000), "particles");

sf::RectangleShape p;

sf::Vector2i mpos;

float zoom;

sf::Clock ctr;

bool mpressed;
bool rpressed;

//bool finished;

float sqrt2(sf::Vector2f dif)
{
	return sqrt((dif.x * dif.x) + (dif.y * dif.y));
}

sf::Vector2f normalise(sf::Vector2f dif)
{
	float sqroot = sqrt2(dif);
	return sf::Vector2f(dif.x / sqroot, dif.y / sqroot);
}

void update(unsigned int t)
{
	float tsize = size / 4;
	//std::cout << tsize << std::endl;
	for (unsigned int i = tsize * (t - 1); i < tsize * t; i++)
	{
		if (mpressed)
		{
			sf::Vector2f dif = pos[i] - sf::Vector2f(mpos);
			sf::Vector2f normalised = normalise(dif);
			vel[i] -= sf::Vector2f(normalised.x / 5, normalised.y / 5);
		}
		if (rpressed)
		{
			sf::Vector2f dif = pos[i] - sf::Vector2f(mpos);
			sf::Vector2f normalised = normalise(dif);
			vel[i] += sf::Vector2f(normalised.x / 5, normalised.y / 5);
		}

		float curdif = abs(vel[i].x) + abs(vel[i].y) + ((sin(ctr.getElapsedTime().asMilliseconds() / 300) * 1.5) + 1.5);

		cs[i].b = 255;
		if (curdif * 20  > 255)
		{
			cs[i].r = 255;
		}
		else
		{
			cs[i].r = curdif * 20;
		}
		//cs[i].r = curdif * 30;
		vel[i].x *= 0.99;
		vel[i].y *= 0.99;
		pos[i] += sf::Vector2f(vel[i].x * 3, vel[i].y * 3);
	}
	//finished = true;
}

sf::Thread t1(&update, 1);
sf::Thread t2(&update, 2);
sf::Thread t3(&update, 3);
sf::Thread t4(&update, 4);

int main()
{
	window.setMouseCursorVisible(false);
	for (unsigned int i = 0; i < size; i++)
	{
		std::uniform_int_distribution<int> x(0, window.getSize().x);
		std::uniform_int_distribution<int> y(0, window.getSize().y);
		pos.push_back(sf::Vector2f(x(rng), y(rng)));
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

		//finished = false;
		t1.launch();
		t2.launch();
		t3.launch();
		t4.launch();
		p.setSize(sf::Vector2f(zoom * 1, zoom * 1));
		p.setFillColor(sf::Color::Yellow);
		for (unsigned int i = 0; i < pos.size(); i++)
		{
			p.setFillColor(cs[i]);
			p.setPosition(pos[i].x * zoom, pos[i].y * zoom);
			window.draw(p);
		}
		p.setSize(sf::Vector2f(4, 4));
		p.setFillColor(sf::Color(255, 0, 255));
		p.setPosition(mpos.x * zoom, mpos.y * zoom);
		window.draw(p);

		//while (!finished);

		window.display();
	}
	return 0;
}