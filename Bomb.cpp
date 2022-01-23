#include "Bomb.h"


Bomb::Bomb(Texture *texture, BombType Type, float speed, Font *font, char Word, float switchTime) {
    srand((unsigned int) time(nullptr));
    if (Type == NULL) setRndType();
    else this->type = Type;

    if (Word == NULL) setRndWord();
    else this->word = Word;

    this->switchTime = switchTime;
    totalTime = 0.0f;

    velocity.x = 0;
    velocity.y = speed;
    BombAnim = {0, 0};

    setRndPosition();
    Body.setSize(bombSize);
    Body.setOrigin(bombSize.x / 2.0f - 25, bombSize.y / 2.0f - 30);
    Char.setString(word);
    Char.setCharacterSize(20);
    Char.setFont(*font);
    Char.setFillColor(Color::Black);
    Char.setOrigin(Vector2f(Char.getLocalBounds().left + Char.getLocalBounds().width / 2.0f,
                            Char.getLocalBounds().top + Char.getLocalBounds().height / 2.0f));

    Body.setTexture(texture);
}

Bomb::~Bomb() {
}

void Bomb::Draw(RenderWindow &window) {
    Update(switchTime / 10.0f);
    window.draw(Body);
    window.draw(Char);
}

void Bomb::Reset() {
    setRndPosition();
    setRndWord();
    Char.setString(word);
    Char.setOrigin(Vector2f(Char.getLocalBounds().left + Char.getLocalBounds().width / 2.0f,
                            Char.getLocalBounds().top + Char.getLocalBounds().height / 2.0f));
}

void Bomb::OnCollision(Vector2f direction) {
    if (direction.y < 0.0f) velocity.y = 0.0f;    //Collisione in basso
}

void Bomb::Update(float deltaTime) {
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        BombAnim.x++;
        if (BombAnim.x > 2) BombAnim.x = 0;
        Body.setTextureRect(IntRect(BombAnim.x * 76, 0 * 148, 76, 148));
        Body.move(Vector2f(velocity * deltaTime));
        Char.setPosition(Vector2f(Body.getPosition().x + 25, Body.getPosition().y + 60));
    }

}