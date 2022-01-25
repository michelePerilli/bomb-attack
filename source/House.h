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
    default_random_engine generator;

public:

    House(Texture *texture, HouseType type, int x) {

        houseTexture = texture;
        this->x = x;
        uniform_int_distribution<int> distribution(0, 1);
        switch (type) {
            case big:
                generateBigHouse();
                break;
            case small:
                generateNewHouse1();
                break;
            case mini:
                generateNewHouse2();
                break;
            case townhall:
                generateTownHall();
                break;
        }


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


    /*void generateHouse(HouseType type) {
        const IntRect rectBigHouse(0, 2, 3, 0);
        const IntRect rectSmallHouse(2, 4, 1, 0);
        const IntRect rectMiniHouse(2, 4, 3, 2);

        IntRect c;
        switch (type) {
            case big:
                c = rectBigHouse;

                break;
            case small:
                c = rectSmallHouse;
                break;
            case mini:
                c = rectMiniHouse;
                break;
            case townhall:
                c = c;
                break;
        }

        house.clear();
        for (int i = 0; i < 2; i++)
            for (int j = 3; j >= 0; j--) {
                int x = flip ? 2 - i + 5 : i;
                house.emplace_back(Block(Vector2i(x, j),
                                         houseTexture,
                                         Vector2i(i + position.x, j + position.y)));
            }
    }*/

    void generateBigHouse() {
        house.clear();
//        generateNewHouse1();
        for (int i = 0; i < 2; i++)
            for (int j = 3; j >= 0; j--) {
//                int z = flip ? 2 - i + 5 : i;
                house.emplace_back(Block(Vector2i(i, j),
                                         houseTexture,
                                         Vector2i(i + this->x, j)));
            }
    }

    void generateSmallHouse() {
        house.clear();
        for (int i = 2; i < 4; i++)
            for (int j = 1; j >= 0; j--) {
                house.emplace_back(Block(Vector2i(i, j),
                                         houseTexture,
                                         Vector2i(i + this->x - 2, j + 2)));
            }
    }

    void generateMiniHouse() {
        house.clear();
        for (int i = 2; i < 4; i++)
            for (int j = 3; j >= 2; j--) {
                house.emplace_back(Block(Vector2i(i, j),
                                         houseTexture,
                                         Vector2i(i + this->x - 2, j)));
            }
    }

    void generateTownHall() {
        house.clear();
        for (int i = 0; i < 3; i++)
            for (int j = 3; j >= 0; j--) {
                house.emplace_back(Block(Vector2i(i, j), nullptr, Vector2i(i + this->x - 0, j)));
            }
    }

    void generateNewHouse1() {
        house.clear();
        for (int i = 4; i < 6; i++)
            for (int j = 2; j >= 0; j--) {
                house.emplace_back(Block(Vector2i(i, j + 1),
                                         houseTexture,
                                         Vector2i(i + this->x - 4, j + 1)));
            }
    }

    void generateNewHouse2() {
        house.clear();
        for (int i = 6; i < 8; i++)
            for (int j = 2; j >= 0; j--) {
                house.emplace_back(Block(Vector2i(i, j + 1),
                                         houseTexture,
                                         Vector2i(i + this->x - 6, j + 1)));
            }
    }

};

