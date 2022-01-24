#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Collider {
private:
    RectangleShape &body;

public:
    explicit Collider(RectangleShape &body) :
            body(body) {
    };

    ~Collider() = default;


    bool isColliding(const Collider &other, const Vector2f &dir, float push) {
        Vector2f direction = dir;

        Vector2f otherPosition = other.getPosition();
        Vector2f otherHalfSize = other.getHalfSize();
        Vector2f thisPosition = getPosition();
        Vector2f thisHalfSize = getHalfSize();

        float deltaX = (otherPosition.x - thisPosition.x);
        float deltaY = otherPosition.y - thisPosition.y;
        float intersectX = (abs(deltaX) - (otherHalfSize.x + thisHalfSize.x));
        float intersectY = (abs(deltaY) - (otherHalfSize.y + thisHalfSize.y));

        if (intersectX < 0.0f && intersectY < 0.0f) {
            push = min(max(push, 0.0f), 1.0f);

            if (intersectX > intersectY) {
                if (deltaX > 0.0f) {
                    move(intersectX * (1.0f - push), 0.0f);
                    other.move(-intersectX * push, 0.0f);

                    direction.x = 1.0f;
                    direction.y = 0.0f;

                } else {
                    move(-intersectX * (1.0f - push), 0.0f);
                    other.move(intersectX * push, 0.0f);

                    direction.x = -1.0f;
                    direction.y = 0.0f;

                }
            } else {
                if (deltaY > 0.0f) {
                    move(0.0f, intersectY * (1.0f - push));
                    other.move(0.0f, -intersectY * push);

                    direction.x = 0.0f;
                    direction.y = 1.0f;

                } else {
                    move(0.0f, -intersectY * (1.0f - push));
                    other.move(0.0f, intersectY * push);

                    direction.x = 0.0f;
                    direction.y = -1.0f;
                }
            }

            return true;

        }

        return false;
    }

    void move(float dx, float dy) const {
        body.move(dx, dy);
    }

    Vector2f getPosition() const {
        return body.getPosition();
    }

    Vector2f getHalfSize() const {
        return {body.getSize().x / 2.0f, body.getSize().y / 2.0f};
    }


};

