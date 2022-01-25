//
// Created by Michele on 24/01/2022.
//

#ifndef BOMB_ATTACK_BLOCK_H
#define BOMB_ATTACK_BLOCK_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>
#include "Constants.h"

using namespace std;

class Block : Entity {

public:
    Block(Vector2i piece, Texture *texture, Vector2i pos)
            : Entity(texture, pos, Vector2i(ENTITY_SIZE, ENTITY_SIZE)) {
        cout << piece.x << " " << piece.y << endl;
        if (piece.x < 5)
            body.setTextureRect(
                    IntRect(piece.x * IMG_BLOCK_WIDTH, piece.y * IMG_BLOCK_HEIGHT,
                            IMG_BLOCK_WIDTH, IMG_BLOCK_HEIGHT));
        else
            body.setTextureRect(IntRect((piece.x - 5) * IMG_BLOCK_WIDTH,piece.y * IMG_BLOCK_HEIGHT,
                                         -IMG_BLOCK_WIDTH, IMG_BLOCK_HEIGHT));
        body.setPosition(Vector2f((float) (pos.x * 50) - 675, (float) (pos.y * 50) + 183));
    }

    ~Block() = default;


    void destroy() {
        body.setPosition(Vector2f(-1000, -1000));
    }


    Collider getCollider() {
        return Collider(body);
    }

    void draw(RenderWindow &window) {
        window.draw(body);
    }


};


#endif //BOMB_ATTACK_BLOCK_H
