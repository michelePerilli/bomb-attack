#include "Bomb.h"
#include "Casa.h"

#define IMG_BOMB_PATH "../data/images/bombe.png"
#define IMG_HOUSE_PATH "../data/images/house.png"
#define IMG_BACKGROUND_PATH "../data/images/sfondo.png"
#define OTF_ADOBE_GOTHIC_BOLD_PATH "../data/fonts/AdobeGothicStd-Bold.otf"

static const unsigned int winX = 1366, winY = 768; //Dimensione finestra

void resizeView(const RenderWindow &window, View &view) //Funzione settaggio camera
{
    float aspRatioX = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(float(winX * aspRatioX), float(winX));
}

void spawnCity(vector<Casa> &Case, Texture &houseTexture) {
    int x = 0;
    for (int n = 0; n < 13; n++) {
        if (n >= 7) x = 1;
        if (n != 6) {
            switch (rand() % 8) {
                case 0:
                    for (int i = 0; i < 2; i++)
                        for (int j = 3; j >= 0; j--)
                            Case.emplace_back(Vector2i(2 - i + 5, j), &houseTexture, Vector2u(i + x + 2 * n, j), false);
                    break;
                case 1:
                    for (int i = 0; i < 2; i++)
                        for (int j = 3; j >= 0; j--)
                            Case.emplace_back(Vector2i(i, j), &houseTexture, Vector2u(i + x + 2 * n, j), false);
                    break;
                case 2:
                case 3:
                    for (int i = 2; i < 4; i++)
                        for (int j = 1; j >= 0; j--)
                            Case.emplace_back(Vector2i(4 - i + 7, j), &houseTexture, Vector2u(i + x + 2 * n - 2, j + 2),
                                              false);
                    break;
                case 4:
                    for (int i = 2; i < 4; i++)
                        for (int j = 1; j >= 0; j--)
                            Case.emplace_back(Vector2i(i, j), &houseTexture, Vector2u(i + x + 2 * n - 2, j + 2), false);
                    break;
                case 5:
                case 6:
                    for (int i = 2; i < 4; i++)
                        for (int j = 3; j >= 2; j--)
                            Case.emplace_back(Vector2i(4 - i + 7, j), &houseTexture, Vector2u(i + x + 2 * n - 2, j),
                                              false);
                    break;
                case 7:
                    for (int i = 2; i < 4; i++)
                        for (int j = 3; j >= 2; j--)
                            Case.emplace_back(Vector2i(i, j), &houseTexture, Vector2u(i + x + 2 * n - 2, j), false);
                    break;
            }
        } else;//for (int i = 0; i < 3; i++) for (int j = 3; j >= 0; j--) Case.push_back(Casa(Vector2i(i, j), nullptr, Vector2u(i + x + 2 * n, j), false));
    }
}

void lose(RenderWindow &window) {
    Texture losing;
    losing.loadFromFile("../data/images/lose.png");
    RectangleShape loseImage;
    loseImage.setTexture(&losing);
    loseImage.setOrigin(Vector2f(float(winX) / 4, float(winX) / 4));
    loseImage.setPosition(Vector2f(0, 0));
    loseImage.setSize(Vector2f(float(winX) / 2, float(winX) / 2));
    window.clear();
    window.draw(loseImage);
}

int main() {

    RenderWindow window(VideoMode(winX, winY), "Bomb Attack", Style::Close | Style::Fullscreen);

    Texture bombTexture;
    bombTexture.loadFromFile(IMG_BOMB_PATH);
    Texture houseTexture;
    houseTexture.loadFromFile(IMG_HOUSE_PATH);
    Texture sfondo;
    sfondo.loadFromFile(IMG_BACKGROUND_PATH);
    Font font;
    font.loadFromFile(OTF_ADOBE_GOTHIC_BOLD_PATH);

    RectangleShape Sfondo;
    Sfondo.setTexture(&sfondo);
    Sfondo.setSize(Vector2f(2048 * 1.1f, 768 * 1.1f));
    Sfondo.setOrigin(Vector2f(1012 * 1.1f, 359 * 1.1f));
    Sfondo.setPosition(Vector2f(0, 0));

    Text dats;
    dats.setCharacterSize(10);
    dats.setFillColor(Color::Black);
    dats.setFont(font);
    dats.setPosition(-Vector2f(float(winX) / 2, float(winY) / 2));


    View view(Vector2f(0.0f, 0.0f), Vector2f(float(winX), float(winY)));
    vector<Casa> houses;

    spawnCity(houses, houseTexture);

    vector<Bomb> bombs;

    bool lost = false;
    float tot = 0, delta = 0.1f, swi = 50;
    int bombe = 0, point = 0;
    std::default_random_engine generator;

    while (window.isOpen()) {
        Event e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    resizeView(window, view);
                    break;
                default:
                    break;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

        window.clear();

        if (tot >= swi && bombe < 15 && !lost) {
            tot -= swi;
            std::uniform_int_distribution<int> distribution(0, 29);
            int number = distribution(generator);
            bombs.emplace_back(&bombTexture, easy, ((float) number / 10.0f) + 1.0f, &font, NULL, 10.0f);
            bombe++;
        }

        if (!lost) {

            window.setView(view);
            window.draw(Sfondo);
            tot += delta;

            for (Casa &casa : houses) {
                for (Bomb &bomb : bombs) {
                    if (casa.getCollider().isColliding(bomb.getCollider(), Vector2f(0.0f, 0.0f), 1.0f)) {
                        casa.destroy();
                        bomb.setRndPosition();
                    }
                    if (bomb.getPosition().y > 350.0f) lost = true;
                    if (Keyboard::isKeyPressed((Keyboard::Key)(bomb.getCharacter() - 65))) {
                        bomb.reset();
                        point++;
                    }
                }
            }


            for (Casa &casa : houses)
                casa.draw(window);

            for (Bomb &bomb : bombs)
                bomb.draw(window);

        } else lose(window);


        dats.setString(to_string(point));
        window.draw(dats);
        window.display();
    }

}