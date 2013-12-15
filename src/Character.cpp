#include "Character.hpp"

Character::Character()
:	anim(2,0,3.0f)
,	x(30.0f)
,	y(30.0f)
,	pressingDown(false)
,	pressingUp(false)
,	pressingLeft(false)
,	pressingRight(false)
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
}

void Character::Draw() {
	anim.Draw(x,y);
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
