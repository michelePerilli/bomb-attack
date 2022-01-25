#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Collider.h"
#include "Block.h"

using namespace std;
using namespace sf;

enum HouseType {
    big, small, mini, townhall
};

class House {
private:
    vector<Block> house;
    int x;
    Texture *houseTexture;

public:

    House(Texture *texture, HouseType type, int x) {

        houseTexture = texture;
        this->x = x;
        generateHouse(type);

    }


    ~House() = default;

    vector<Block> *getBlockList() {
        return &house;
    }

    void draw(RenderWindow &window) {
        for (Block block: house) {
            block.draw(window);
        }
    }


    void generateHouse(HouseType type) {
        int height = type == big || type == townhall ? 5 : 3;
        int width = type == townhall ? 3 : 2;

        house.clear();
        for (int i = (type * width); i < width + (type * width); i++)
            for (int j = height; j > 0; j--) { // l'origine nell'immagine e' in alto a sinistra

                house.emplace_back(Block(houseTexture,
                                         Vector2i(i + 1, j),
                                         Vector2i(i + this->x - (type * width), j)));
            }

    }
};

