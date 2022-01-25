//
// Created by Michele on 24/01/2022.
//

#ifndef BOMB_ATTACK_ENTITY_H
#define BOMB_ATTACK_ENTITY_H

#include "Collider.h"

class Entity {
public:
    RectangleShape body;
    default_random_engine generator;

    Entity(Texture *texture, Vector2i pos, Vector2i size) {
        body.setTexture(texture);
        body.setSize(Vector2f((float) size.x, (float) size.y));
        body.setPosition(Vector2f((float) pos.x, (float) pos.y));
        generator.seed(time(nullptr));
    }


};


#endif //BOMB_ATTACK_ENTITY_H
