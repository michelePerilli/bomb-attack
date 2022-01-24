//
// Created by Michele on 24/01/2022.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Casa.h"
#include "Constants.h"
#include <ctime>

class GameEngine {
private:
    unsigned int winX = 1366, winY = 768; //Dimensione finestra
    RenderWindow window;
    Texture bombTexture;
    Texture houseTexture;
    Texture foreground;
    Texture losing;

    RectangleShape background;
    RectangleShape loseImage;
    Text points;
    Font font;

    vector<Casa> city;
    vector<Bomb> bombs;

    std::default_random_engine generator;

    bool lost = false;
    float tot = 0.0f, delta = 0.1f, swi = 50.0f;

    int bombCount = 0, pointCount = 0;

    View view;

public:
    GameEngine() {
        window.create(VideoMode(winX, winY), "Bomb Attack", Style::Close);
        view.setCenter(Vector2f(0.0f, 0.0f));
        view.setSize(Vector2f(float(winX), float(winY)));

        bombTexture.loadFromFile(IMG_BOMB_PATH);
        houseTexture.loadFromFile(IMG_HOUSE_PATH);
        foreground.loadFromFile(IMG_BACKGROUND_PATH);
        font.loadFromFile(OTF_ADOBE_GOTHIC_BOLD_PATH);
        losing.loadFromFile(IMG_LOST_PATH);

        background.setTexture(&foreground);
        background.setSize(Vector2f(2048 * 1.1f, 768 * 1.1f));
        background.setOrigin(Vector2f(1012 * 1.1f, 359 * 1.1f));
        background.setPosition(Vector2f(0, 0));

        points.setCharacterSize(10);
        points.setFillColor(Color::Black);
        points.setFont(font);
        points.setPosition(-Vector2f(float(winX) / 2, float(winY) / 2));

        loseImage.setTexture(&losing);
        loseImage.setOrigin(Vector2f(float(winX) / 4, float(winX) / 4));
        loseImage.setPosition(Vector2f(0, 0));
        loseImage.setSize(Vector2f(float(winX) / 2, float(winX) / 2));


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
            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

            window.clear();

            if (tot >= swi && bombCount < 15 && !lost) {
                tot -= swi;
                std::uniform_int_distribution<int> distribution(0, 29);
                int number = distribution(generator);
                bombs.emplace_back(&bombTexture, easy, ((float) number / 10.0f) + 1.0f, &font, NULL, 10.0f);
                bombCount++;
            }

            if (!lost) {

                window.setView(view);
                window.draw(background);
                tot += delta;

                for (Casa &casa : city) {
                    for (Bomb &bomb : bombs) {
                        if (casa.getCollider().isColliding(bomb.getCollider(), Vector2f(0.0f, 0.0f), 1.0f)) {
                            casa.destroy();
                            bomb.setRndPosition();
                        }
                        if (bomb.getPosition().y > 350.0f) lost = true;
                        if (Keyboard::isKeyPressed((Keyboard::Key)(bomb.getCharacter() - 65))) {
                            bomb.reset();
                            pointCount++;
                        }
                    }
                }


                for (Casa &casa : city)
                    casa.draw(window);

                for (Bomb &bomb : bombs)
                    bomb.draw(window);

            } else {
                lose();
            }


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
//                uniform_int_distribution<int> distribution(0, 7);
//                int number = distribution(generator);
                switch (rand() % 8) {
                    case 0:
                        generateBigHouse(writePosition, true);
                        break;
                    case 1:
                        generateBigHouse(writePosition, false);
                        break;
                    case 2:
                    case 3:
                        generateMiniHouse(writePosition, true);
                    case 4:
                        generateMiniHouse(writePosition, false);
                        break;
                    case 5:
                    case 6:
                        generateSmallHouse(writePosition, true);
                        break;
                    case 7:
                        generateSmallHouse(writePosition, false);
                        break;
                    default:
                        return;
                }
                writePosition += 2;
            } else {
                generateTownHall(writePosition, false);
                writePosition += 3;
            }
        }
    }

    void generateBigHouse(int position, bool flip) {
        for (int i = 0; i < 2; i++)
            for (int j = 3; j >= 0; j--) {
                int x = flip ? 2 - i + 5 : i;
                city.emplace_back(Vector2i(x, j),
                                  &houseTexture,
                                  Vector2u(i + position, j));
            }
    }

    void generateSmallHouse(int position, bool flip) {
        for (int i = 2; i < 4; i++)
            for (int j = 1; j >= 0; j--) {
                int x = flip ? 4 - i + 7 : i;
                city.emplace_back(Vector2i(x, j), &houseTexture,
                                  Vector2u(i + position - 2, j + 2));
            }
    }

    void generateMiniHouse(int position, bool flip) {
        for (int i = 2; i < 4; i++)
            for (int j = 3; j >= 2; j--) {
                int x = flip ? 4 - i + 7 : i;
                city.emplace_back(Vector2i(x, j),
                                  &houseTexture,
                                  Vector2u(i + position - 2, j));
            }
    }

    void generateTownHall(int position, bool flip) {//todo flip
        for (int i = 0; i < 3; i++)
            for (int j = 3; j >= 0; j--) {
                int x = flip ? 3 - i + 5 : i;
                city.emplace_back(Vector2i(x, j), nullptr, Vector2u(i + position, j));
            }
    }

};


