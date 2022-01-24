#pragma once

#include <ctime>
#include <random>
#include "Collider.h"
#include "Constants.h"

enum BombType {
    easy, medium, hard, heavy
};

class Bomb {


private:
    const Vector2f bombSize{50.0f, 100.0f};

    Vector2f velocity;
    Vector2u bombAnim;

    float totalTime, switchTime, animTimer;

    Texture bombTexture;
    Font font;

    BombType type;
    RectangleShape body;
    Text character;
    char word;

    std::default_random_engine generator;

public:
    Bomb(Texture *texture, BombType type, float speed, Font *font, char word, float switchTime) {
        generator.seed(time(nullptr));
        animTimer = 0;
        if (type == (BombType) NULL)
            setRndType();
        else
            this->type = type;

        setRndWord();

        this->switchTime = switchTime;
        totalTime = 0.0f;

        velocity.x = 0;
        velocity.y = speed;
        bombAnim = {0, 0};

        setRndPosition();
        body.setSize(bombSize);
        body.setOrigin(bombSize.x / 2.0f - 25, bombSize.y / 2.0f - 30);

        character.setString(this->word);
        character.setCharacterSize(20);
        character.setFont(*font);
        character.setFillColor(Color::Black);
        character.setOrigin(Vector2f(character.getLocalBounds().left + character.getLocalBounds().width / 2.0f,
                                     character.getLocalBounds().top + character.getLocalBounds().height / 2.0f));

        body.setTexture(texture);
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
            character.setPosition(Vector2f(body.getPosition().x + 25, body.getPosition().y + 60));
        }
    }

    void updateAnimation() {
        animTimer += 2;
        if (animTimer >= 100) {
            animTimer -= 100;
            bombAnim.x++;
            if (bombAnim.x > 2)
                bombAnim.x = 0;
            body.setTextureRect(IntRect((int) bombAnim.x * 76, 0 * 148, 76, 148));
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
        std::uniform_int_distribution<int> distribution(0, 25);
        int number = distribution(generator);
        // Non mi ricordo assolutamente che razza di calcolo era
        body.setPosition(Vector2f((float) ((number - 13) * 50) - 25, -500));
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

