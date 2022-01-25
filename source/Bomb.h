#pragma once

#include <ctime>
#include <random>
#include "Collider.h"
#include "Constants.h"
#include "Entity.h"

enum BombType {
    easy, medium, hard, heavy
};

class Bomb : Entity {


private:

    Vector2f velocity;
    Vector2u bombAnim;

    float totalTime, switchTime, animTicks;

    BombType type;
    Text character;
    char word;

public:
    Bomb(Texture *texture, Font *font, Vector2i size, float speed, float switchTime)
            : Entity(texture, Vector2i(0, -500), size) {


        animTicks = 0;

        setRndType();
        setRndWord();
        setRndPosition();

        this->switchTime = switchTime;
        totalTime = 0.0f;

        velocity.x = 0;
        velocity.y = speed;
        bombAnim = {0, 0};

//        body.setOrigin(float(size.x) / 2.0f - 25, float(size.y) / 2.0f - 30);

        character.setString(this->word);
        character.setCharacterSize(20);
        character.setFont(*font);
        character.setFillColor(Color::Black);
        character.setOrigin(Vector2f(character.getLocalBounds().left + character.getLocalBounds().width / 2.0f,
                                     character.getLocalBounds().top + character.getLocalBounds().height / 2.0f));

    }

    ~Bomb() = default;

    void update(float deltaTime) {
        updatePosition(deltaTime);
        updateAnimation();
    }

    void updatePosition(float deltaTime) {
        totalTime += deltaTime;

        if (totalTime >= switchTime) {
            totalTime -= switchTime;
            body.move(Vector2f(velocity * deltaTime));
            character.setPosition(Vector2f(body.getPosition().x, body.getPosition().y + 30));
        }
    }

    void updateAnimation() {
        animTicks += 2;
        if (animTicks >= 100) {
            animTicks -= 100;
            bombAnim.x++;
            if (bombAnim.x > 2)
                bombAnim.x = 0;
            body.setTextureRect(
                    IntRect((int) bombAnim.x * IMG_BOMB_WIDTH, 0 * IMG_BOMB_HEIGHT, IMG_BOMB_WIDTH, IMG_BOMB_HEIGHT));
        }
    }


    void draw(RenderWindow &window) {
        update(switchTime / 10.0f);
        window.draw(body);
        window.draw(character);
    }

    void reset() {
        setRndPosition();
        setRndWord();
        character.setString(word);
        character.setOrigin(Vector2f(character.getLocalBounds().left + character.getLocalBounds().width / 2.0f,
                                     character.getLocalBounds().top + character.getLocalBounds().height / 2.0f));
    }

    void onCollision(Vector2f direction) {
        if (direction.y < 0.0f) velocity.y = 0.0f;    //Collisione in basso
    }

    void setRndType() {
        std::uniform_int_distribution<int> distribution(easy, heavy);
        type = BombType(distribution(generator));
    }

    void setRndWord() {

        std::uniform_int_distribution<int> distribution('A', 'Z');
        word = (char) distribution(generator);
    }

    void setRndPosition() {
        std::uniform_int_distribution<int> distribution(0, 26);
        int number = distribution(generator);
        // Non mi ricordo assolutamente che razza di calcolo era
        body.setPosition(Vector2f((float) -(number * 50) - 33, -1000));
        character.setPosition(body.getPosition());
    }


    Collider getCollider() {
        return Collider(body);
    }

    void move(Vector2f direct) {
        body.move(direct);
    }

    Vector2f getPosition() {
        return body.getPosition();
    }

    char getCharacter() const {
        return word;
    }


};

