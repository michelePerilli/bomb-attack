#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Collider {
public:
    explicit Collider(RectangleShape &body);

    ~Collider();

    void Move(float dx, float dy) { body.move(dx, dy); }

    bool isColliding(Collider &other, Vector2f &direction, float push);

    Vector2f GetPosition() { return body.getPosition(); }

    Vector2f GetHalfSize() { return {body.getSize().x / 2.0f, body.getSize().y / 2.0f}; }

private:
    RectangleShape &body;

};

