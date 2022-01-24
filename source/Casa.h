#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Collider.h"

using namespace std;
using namespace sf;

class Casa {
private:
    RectangleShape casa;
public:
    Casa(Vector2i piece, Texture *texture, Vector2u pos) {
        casa.setTexture(texture);
        if (piece.x < 5) casa.setTextureRect(IntRect(piece.x * 48, piece.y * 48, 48, 48));
        else casa.setTextureRect(IntRect((piece.x - 5) * 48, piece.y * 48, -48, 48));
        casa.setSize(Vector2f(50, 50));
        casa.setPosition(Vector2f((float) (pos.x * 50) - 675, (float) (pos.y * 50) + 183));

    }

    ~Casa() = default;


    void destroy() {
        casa.setPosition(Vector2f(-1000, -1000));
    }

    Collider getCollider() {
        return Collider(casa);
    }


    void draw(RenderWindow &window) {
        window.draw(casa);
    }


};

