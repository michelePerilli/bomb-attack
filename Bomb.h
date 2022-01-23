#pragma once
#include <ctime>
#include "Collider.h"

enum BombType {easy, medium, hard, heavy};

class Bomb
{
public:
	Bomb(Texture* texture, BombType Type, float speed, Font* font, char Word, float switchTime);
	~Bomb();

	void setRndType() { type = BombType(rand() % 4); }
	void setRndWord() { word = (rand() % 26) + 65; }
	void setRndPosition() { Body.setPosition(Vector2f((float)(((rand() % 26) - 13) * 50) - 25, -500)); Char.setPosition(Body.getPosition()); }

	void Update(float deltaTime);
	void Draw(RenderWindow &window);
	void Reset();

	void OnCollision(Vector2f direction);
	Collider GetCollider() { return Collider(Body); }

	void move(Vector2f direct) { Body.move(direct); }

	Vector2f GetPosition() { return Body.getPosition(); }
	char GetChar() { return word; }


private:
	const Vector2f bombSize{ 50.0f, 100.0f };

	Vector2f velocity;
	Vector2u BombAnim;
	
	float totalTime, switchTime;

	BombType type;
	RectangleShape Body;
	Text Char;
	char word;
};

