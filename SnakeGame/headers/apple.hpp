#ifndef APPLE_HPP
#define APPLE_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Apple {
private:
    RectangleShape sprite;

public:
    Apple();

    void setPosition(Vector2f newPosition);
    RectangleShape getSprite();
};

#endif //APPLE_HPP
