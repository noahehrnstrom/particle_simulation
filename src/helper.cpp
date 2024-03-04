#include "../include/helper.hpp"

int genRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

float sqrt2(sf::Vector2f dif)
{
    return sqrt((dif.x * dif.x) + (dif.y * dif.y));
}

sf::Vector2f normalise(sf::Vector2f dif)
{
    float sqroot = sqrt2(dif);
    return sf::Vector2f(dif.x / sqroot, dif.y / sqroot);
}