#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "Collider.h"

using namespace std;
using namespace sf;

class Casa
{
public:
	Casa(Vector2i piece, Texture* texture, Vector2u pos, bool townHall);
	~Casa();

	Vector2f GetPosition() { return casa.getPosition(); }
	void Destroy() { casa.setPosition(Vector2f(-1000, -1000)); }
	Collider GetCollider() { return Collider(casa); }
	void Move(Vector2f direct) { casa.move(direct); }
	void Draw(RenderWindow& window) { window.draw(casa); }
private:
	RectangleShape casa;
};

