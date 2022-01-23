#include "Casa.h"

Casa::Casa(Vector2i piece, Texture * texture, Vector2u pos, bool townHall)
{
	casa.setTexture(texture);
	if (piece.x < 5) casa.setTextureRect(IntRect(piece.x * 48, piece.y * 48, 48, 48));
	else casa.setTextureRect(IntRect((piece.x-5) * 48, piece.y * 48, -48, 48));
	casa.setSize(Vector2f(50, 50));
	casa.setPosition(Vector2f((pos.x * 50.0f) - 675.0f, (pos.y * 50.0f) + 183));
	
}


Casa::~Casa()
{
}


