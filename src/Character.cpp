#include <cmath>
//#include <allegro5/allegro_primitives.h>
#include "Character.hpp"

#define SIZE 0.9f

Character::Character(Map* m)
:	anim(2,0,3.0f)
,	pressingUp(false)
,	pressingDown(false)
,	pressingLeft(false)
,	pressingRight(false)
,	x(30.0f)
,	y(100.0f)
,	_map(m)
{
}

Character::~Character()
{
}

inline bool Xor(bool a, bool b) {
	return (a && !b) || (!a && b);
}

void Character::Update(const float deltaT) {

	float speed = 100.0f * deltaT;

	if (Xor(pressingUp, pressingDown)) {
		if (pressingUp) {
			y -= speed;
			anim.anim = 3;
		}
		if (pressingDown) {
			y += speed;
			anim.anim = 0;
		}
	}

	if (Xor(pressingLeft, pressingRight)) {
		if (pressingLeft) {
			x -= speed;
			anim.anim = 1;
		}
		if (pressingRight) {
			x += speed;
			anim.anim = 2;
		}
	}

	if (Xor(pressingUp, pressingDown) || Xor(pressingLeft, pressingRight)) {
		anim.framerate = 6.0f;
	}
	else {
		anim.framerate = 0.0f;
		anim.SetFrame(1);
	}

	// collision
	x /= _map->get_largeur_case();
	y /= _map->get_hauteur_case();

	float lx = fmodf(x, 1.0f);
	float ly = fmodf(y, 1.0f);

	int px = (int) x;
	int py = (int) y;

	int cx = lx < 0.5f ? -1 : 1;
	int cy = ly < 0.5f ? -1 : 1;

	float colx = cx < 0 ? floorf(x) : ceilf(x);
	float coly = cy < 0 ? floorf(y) : ceilf(y);

	if (!IsCellFree(px, py+cy)) {
		MoveFrom(x,coly);
	}

	if (!IsCellFree(px+cx, py)) {
		MoveFrom(colx,y);
	}

	if (!IsCellFree(px+cx, py+cy)) {
		MoveFrom(colx,coly);
	}

	x *= _map->get_largeur_case();
	y *= _map->get_hauteur_case();
}

void Character::MoveFrom(float colx, float coly) {
	float s = SIZE * 0.5f;
	float dirx = colx - x;
	float diry = coly - y;
	float dirsqr = dirx*dirx + diry*diry;
	if (dirsqr < s*s) {
		float l = sqrtf(dirsqr);
		float scl = (l-s)/l;
		x += dirx * scl;
		y += diry * scl;
	}
}

bool Character::IsCellFree(int cx, int cy) {
	const Case* c = _map->get_case(cx * _map->get_largeur_case(), cy * _map->get_hauteur_case());
	if (c) {
		return c->get_libre();
	}
	return true;
}

void Character::Draw() {
	//al_draw_filled_circle(x,y, SIZE * 16.0f, al_map_rgb(255,255,255));
	anim.Draw(x-16,y-16);
}

void Character::Input(const ALLEGRO_EVENT& ev) {
	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			pressingUp = false;
			break;
		case ALLEGRO_KEY_DOWN:
			pressingDown = false;
			break;
		case ALLEGRO_KEY_LEFT:
			pressingLeft = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			pressingRight = false;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			pressingUp = true;
			break;
		case ALLEGRO_KEY_DOWN:
			pressingDown = true;
			break;
		case ALLEGRO_KEY_LEFT:
			pressingLeft = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			pressingRight = true;
			break;
		}
	}
}
