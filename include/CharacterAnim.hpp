#ifndef _CHARACTER_ANIM_H_
#define _CHARACTER_ANIM_H_

#include <allegro5/allegro.h>

class CharacterAnim {

public:
	CharacterAnim(int ch, int an, float fr);
	~CharacterAnim();

	void Draw(float x, float y);

	int character;
	int anim;
	float framerate;

private:

	int curFrame;
	float lastFrameChange;

	static ALLEGRO_BITMAP *image;
	static int useCount;
};

#endif // _CHARACTER_ANIM_H_
