#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Character.hpp"
#include "Map.hpp"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
const string IMG_TERRAIN = "resources/textures.png";

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY     *display     = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER       *timer       = NULL;
	ALLEGRO_BITMAP      *bouncer     = NULL;
	float bouncer_x  = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer_y  = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer_dx = -4.0, bouncer_dy = 4.0;
	bool redraw = true;

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize keyboard!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to load image addon!\n");
		return -1;
	}

	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to load primitives addon!\n");
		return -1;
	}

	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	if(!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	fprintf(stdout, "%s\n", al_get_current_directory());

	al_set_target_bitmap(bouncer);

	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0,0,0));

	al_flip_display();

	al_start_timer(timer);

	{

        Map ma_map(32.0, 32.0, 3, 3, IMG_TERRAIN);
        float source_hauteur = 32.0;
        float source_largeur = 32.0;
        float herbe_x = 3.0;
        float herbe_y = 131.0;
        float lave_x = 67.0;
        float lave_y = 163.0;
        ma_map.ajouter_case(new Case(&ma_map, true, source_largeur, source_hauteur, herbe_x, herbe_y, 0, 0));
        ma_map.ajouter_case(new Case(&ma_map, true, source_largeur, source_hauteur, herbe_x, herbe_y, 0, 1));
        ma_map.ajouter_case(new Case(&ma_map, true, source_largeur, source_hauteur, herbe_x, herbe_y, 0, 2));

        ma_map.ajouter_case(new Case(&ma_map, true, source_largeur, source_hauteur, herbe_x, herbe_y, 1, 0));
		ma_map.ajouter_case(new Case(&ma_map, false, source_largeur, source_hauteur, lave_x, lave_y, 1, 1));
        ma_map.ajouter_case(new Case(&ma_map, true, source_largeur, source_hauteur, herbe_x, herbe_y, 1, 2));

        ma_map.ajouter_case(new Case(&ma_map, true, source_largeur, source_hauteur, herbe_x, herbe_y, 2, 0));
        ma_map.ajouter_case(new Case(&ma_map, true, source_largeur, source_hauteur, herbe_x, herbe_y, 2, 1));
        ma_map.ajouter_case(new Case(&ma_map, true, source_largeur, source_hauteur, herbe_x, herbe_y, 2, 2));

		Character charac(&ma_map);
		float lastTime = al_current_time();

		while(1)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			charac.Input(ev);

			if(ev.type == ALLEGRO_EVENT_TIMER) {
				if(bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE) {
					bouncer_dx = -bouncer_dx;
				}

				if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE) {
					bouncer_dy = -bouncer_dy;
				}

				bouncer_x += bouncer_dx;
				bouncer_y += bouncer_dy;

				redraw = true;
			}
			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}

			if(redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;

				float newTime = al_current_time();
				float deltaTime = newTime - lastTime;
				lastTime = newTime;

				al_clear_to_color(al_map_rgb(0,0,0));
				ma_map.dessiner(display);

				al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

				charac.Update(deltaTime);
				charac.Draw();

				al_flip_display();
			}
		}
	}

	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_shutdown_image_addon();

	return 0;
}
