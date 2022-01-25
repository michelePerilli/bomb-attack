//
// Created by Michele on 24/01/2022.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "House.h"
#include "Constants.h"
#include <ctime>

class GameEngine {
private:
    static const unsigned int winX = 1366;
    static const unsigned int winY = 768; //Dimensione finestra

    Vector2f origin;

    RenderWindow window;
    Texture bombTexture;
    Texture houseTexture;
    Texture foreground;
    Texture losing;

    RectangleShape background;
    RectangleShape loseImage;
    Text points;
    Font font;

    vector<House> city;
    vector<Bomb> bombs;

    std::default_random_engine generator;

    Vector2i bombsSize = {ENTITY_SIZE, ENTITY_SIZE * 2};

    bool lost = false;
    float tot = 0.0f, delta = 0.1f, swi = 50.0f;

    int bombCount = 0, pointCount = 0;

    View view;

public:
    GameEngine() {
        origin = Vector2f(-float(winX) / 2, -float(winY) / 2);

        window.create(VideoMode(winX, winY), "Bomb Attack", Style::Close);
        view.setCenter(origin);
        view.setSize(Vector2f(float(winX), float(winY)));

        bombTexture.loadFromFile(IMG_BOMB_PATH);
        houseTexture.loadFromFile(IMG_HOUSE_PATH);
        foreground.loadFromFile(IMG_BACKGROUND_PATH);
        font.loadFromFile(OTF_ADOBE_GOTHIC_BOLD_PATH);
        losing.loadFromFile(IMG_LOST_PATH);

        background.setTexture(&foreground);
        background.setSize(Vector2f(2048 * 1.1f, 768 * 1.1f));
        background.setOrigin(Vector2f(2048 * 1.1f, 768 * 1.1f));
        background.setPosition(Vector2f(0, 0));

        loseImage.setTexture(&losing);
        loseImage.setOrigin(Vector2f(float(winX) / 2, float(winX) / 2));
        loseImage.setSize(Vector2f(float(winX) / 4, float(winX) / 4));
        loseImage.setPosition(Vector2f(0, 0));

        points.setCharacterSize(10);
        points.setFillColor(Color::Black);
        points.setFont(font);
        points.setPosition(-Vector2f(float(winX), float(winY)));

    }

    void lose() {
        window.clear();
        window.draw(loseImage);
    }

    void start() {
        spawnCity();
        while (window.isOpen()) {
            Event e{};
            while (window.pollEvent(e)) {
                switch (e.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::Resized:
                        resizeView();
                        break;
                    default:
                        break;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            window.clear();

            if (tot >= swi && bombCount < 15 && !lost) {
                tot -= swi;
                std::uniform_int_distribution<int> distribution(0, 29);
                int number = distribution(generator);
                bombs.emplace_back(Bomb(&bombTexture, &font, bombsSize, ((float) number / 10.0f) + 1.0f, 10.0f));
                bombCount++;
            }

            if (!lost) {

                window.setView(view);
                window.draw(background);
                tot += delta;

                for (House &casa : city) {
                    for (Block &block : *casa.getBlockList()) {
                        for (Bomb &bomb : bombs) {
                            if (block.getCollider().isColliding(bomb.getCollider(), Vector2f(0.0f, 0.0f), 1.0f)) {
                                block.destroy();
                                bomb.setRndPosition();
                            }
                            if (bomb.getPosition().y > 0) {
                                // start some kind of animation
                                lost = true;
                            }
                            if (Keyboard::isKeyPressed((Keyboard::Key) (bomb.getCharacter() - 65))) {
                                bomb.reset();
                                pointCount++;
                            }
                        }
                    }


                    for (House &house : city)
                        house.draw(window);

                    for (Bomb &bomb : bombs)
                        bomb.draw(window);

                }
            } else {
                lose();
            }
            RectangleShape center;
            center.setSize(Vector2f(10, 10));
            center.setOrigin(Vector2f(5, 5));
            center.setPosition(Vector2f(0, 0));
            window.draw(center);

            points.setString(to_string(pointCount));
            window.draw(points);
            window.display();
        }
    }


private:

//Funzione settaggio camera
    void resizeView() {
        float aspRatioX = float(window.getSize().x) / float(window.getSize().y);
        view.setSize(float(winX) * aspRatioX, float(winX));
    }

    void spawnCity() {
        int writePosition = 0;
        for (int n = 0; n < 13; n++) {
            if (n != 6) {

                city.emplace_back(House(&houseTexture, (HouseType) (rand() % 3), writePosition));
                writePosition += 2;
            } else {
                city.emplace_back(House(nullptr, townhall, writePosition));
                writePosition += 3;
            }
        }
    }


};


