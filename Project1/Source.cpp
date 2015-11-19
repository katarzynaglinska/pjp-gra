#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include<allegro5\bitmap.h>
#include <allegro5\allegro_image.h>
#include "objects.h"


const int WIDTH = 640;
const int HEIGHT = 480;
enum KEYS { LEFT, RIGHT };
bool keys[5] = { false, false };


void Initkoszyk(mojkoszyk &koszyk);
void Drawkoszyk(mojkoszyk &koszyk);
void MovekoszykLeft(mojkoszyk &koszyk);
void MovekoszykRight(mojkoszyk &koszyk);

int main(void)
{
	//primitive variable
	const int FPS = 60;
	bool done = false;
	bool redraw = true;
	int imagewidth = 0;
	int imageheight = 0;

	//object variables
	mojkoszyk koszyk;

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *image = NULL;

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//Allegro Module Init
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	//Game Init
	Initkoszyk(koszyk);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (keys[LEFT])
				MovekoszykLeft(koszyk);
			if (keys[RIGHT])
				MovekoszykRight(koszyk);
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			}
		}


		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			Drawkoszyk(koszyk);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

void Initkoszyk(mojkoszyk &koszyk)
{
	koszyk.x = 20;
	koszyk.y = 340;
	koszyk.speed = 5;
}
void Drawkoszyk(mojkoszyk &koszyk)
{

	al_draw_filled_rectangle(koszyk.x - 12, koszyk.y - 2, koszyk.x + 70, koszyk.y + 30, al_map_rgb(150, 75, 0));
}
void MovekoszykLeft(mojkoszyk &koszyk)
{
	koszyk.x -= koszyk.speed;
	if (koszyk.x < 0)
		koszyk.x = 0;

}

void MovekoszykRight(mojkoszyk &koszyk)
{
	koszyk.x += koszyk.speed;
	if (koszyk.x > 580)
		koszyk.x = 580;
}