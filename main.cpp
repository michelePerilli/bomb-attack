#include "Bomb.h"
#include "Casa.h"

static const unsigned int winX = 1366, winY = 768; //Dimensione finestra

void ResizeView(const RenderWindow &window, View &view) //Funzione settaggio camera
{
    float aspRatioX = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(float(winX * aspRatioX), float(winX));
}

void SpawnCity(vector<Casa> &Case, Texture &houseTexture) {
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

void Lose(RenderWindow &window) {
    Texture losing;
    losing.loadFromFile("data/imageData/lose.png");
    RectangleShape loseImage;
    loseImage.setTexture(&losing);
    loseImage.setOrigin(Vector2f(float(winX) / 4, float(winX) / 4));
    loseImage.setPosition(Vector2f(0, 0));
    loseImage.setSize(Vector2f(float(winX) / 2, float(winX) / 2));
    window.clear();
    window.draw(loseImage);
}

int main() {
    srand((unsigned int) time(nullptr));

    RenderWindow window(VideoMode(winX, winY), "Bomb Attack", Style::Close | Style::Fullscreen);

    Texture bombTexture;
    bombTexture.loadFromFile("imageData/bombe.png");
    Texture houseTexture;
    houseTexture.loadFromFile("imageData/house.png");
    Texture sfondo;
    sfondo.loadFromFile("imageData/sfondo.png");
    Font font;
    font.loadFromFile("gameData/gameFont.otf");

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
    vector<Casa> Case;

    SpawnCity(Case, houseTexture);

    vector<Bomb> Bombs;

    bool lose = false;
    float tot = 0, delta = 0.1f, swi = 50;
    int bombe = 0, point = 0;

    while (window.isOpen()) {
        Event e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    ResizeView(window, view);
                    break;
                default:
                    break;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

        window.clear();

        if (tot >= swi && bombe < 15 && !lose) {
            tot -= swi;
            Bombs.emplace_back(&bombTexture, easy, (float) ((rand() % 30) / 10.0f) + 1.0f, &font, NULL, 10.0f);
            bombe++;
        }

        if (!lose) {

            window.setView(view);
            window.draw(Sfondo);
            tot += delta;

            for (Casa &casa : Case) {
                for (Bomb &bomb : Bombs) {
                    if (casa.GetCollider().isColliding(bomb.GetCollider(), Vector2f(0.0f, 0.0f), 1.0f)) {
                        casa.Destroy();
                        bomb.setRndPosition();
                    }
                    if (bomb.GetPosition().y > 350.0f) lose = true;
                    if (Keyboard::isKeyPressed((Keyboard::Key) (bomb.GetChar() - 65))) {
                        bomb.Reset();
                        point++;
                    }
                }
            }


            for (Casa &casa : Case) casa.Draw(window);
            for (Bomb &bomb : Bombs) bomb.Draw(window);

        } else Lose(window);


        dats.setString(to_string(point));
        window.draw(dats);
        window.display();
    }

}