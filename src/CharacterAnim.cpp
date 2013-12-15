#include <stdio.h>
#include "CharacterAnim.hpp"

ALLEGRO_BITMAP *CharacterAnim::image = NULL;
int CharacterAnim::useCount = 0;


CharacterAnim::CharacterAnim(int ch, int an, float fr) : character(ch), anim(an), framerate(fr), curFrame(0), lastFrameChange(0.0f) {
	if (useCount == 0 && image == NULL) {
		if (al_filename_exists("resources/persos.png"))
			fprintf(stdout, "YEAH\n");
		else
			fprintf(stdout, "OH NOH\n");

		image = al_load_bitmap("resources/persos.png");
		al_convert_mask_to_alpha(image, al_get_pixel(image,0,0));
	}

	++useCount;
}

CharacterAnim::~CharacterAnim() {
	--useCount;

	if (useCount == 0 && image != NULL) {
		al_destroy_bitmap(image);
		image = NULL;
	}
}

void CharacterAnim::Draw(float x, float y) {
	int bw = al_get_bitmap_width(image);
	int bh = al_get_bitmap_height(image);

	int w = bw / (3*4);
	int h = bh / (4*2);

	if (character > 3) {
		character -= 3;
		anim += 4;
	}

	int frame = (al_get_time() - lastFrameChange) * framerate;
	frame %= 4;
	if (frame == 3)
		frame = 1;

	al_draw_scaled_bitmap( image, (character*3+frame)*w, anim*h, w, h, x, y, w, h, 0 );
}
