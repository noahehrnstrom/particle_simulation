#ifndef HELPER_H
#define HELPER_H

#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>

int genRandomInt(int min, int max);

float sqrt2(sf::Vector2f dif);

sf::Vector2f normalise(sf::Vector2f dif);

#endif