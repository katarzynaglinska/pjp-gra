#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "objects.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>


const int WIDTH = 640;
const int HEIGHT = 480;
const int Jablko_num = 7;
enum KEYS { LEFT, RIGHT };
bool keys[2] = { false, false };


void Initkoszyk(mojkoszyk &koszyk);
void Drawkoszyk(mojkoszyk &koszyk);
void MovekoszykLeft(mojkoszyk &koszyk);
void MovekoszykRight(mojkoszyk &koszyk);

void InitJablko(Jablko jabluszko[], int size);
void DrawJablko(Jablko jabluszko[], int size);
void StartJablko(Jablko jabluszko[], int size);
void UpdateJablko(Jablko jabluszko[], int size);

void EndJablko(Jablko jabluszko[], int size2, mojkoszyk &koszyk);

int main(void)
{
	srand(time(NULL));

	//primitive variable
	const int FPS = 60;
	bool done = false;
	bool redraw = true;
	int imagewidth = 0;
	int imageheight = 0;

	//object variables
	mojkoszyk koszyk;
	Jablko jabluszko[Jablko_num];

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//Allegro Module Init
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	//Game Init
	Initkoszyk(koszyk);
	InitJablko(jabluszko, Jablko_num);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	font = al_load_font("font.ttf", 22, 0);


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


			StartJablko(jabluszko, Jablko_num);
			UpdateJablko(jabluszko, Jablko_num);
			EndJablko(jabluszko, Jablko_num, koszyk);
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
			DrawJablko(jabluszko, Jablko_num);
			al_draw_textf(font, al_map_rgb(255, 0, 255), 20, HEIGHT - 40, 0, "  URATOWANE  %i ", koszyk.uratowane);
			al_draw_textf(font, al_map_rgb(255, 0, 255), WIDTH - 160, HEIGHT - 40, 0, "  STRACONE  %i ", koszyk.stracone);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}


	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

void Initkoszyk(mojkoszyk &koszyk)
{
	koszyk.x = 320;
	koszyk.y = 340;
	koszyk.speed = 5;

	koszyk.xx = 40;
	koszyk.yy = 7;
	koszyk.uratowane = 0;
	koszyk.stracone = 0;
}
void Drawkoszyk(mojkoszyk &koszyk)
{

	al_draw_filled_rectangle(koszyk.x - 40, koszyk.y - 2, koszyk.x + 40, koszyk.y + 30, al_map_rgb(150, 75, 0));
}
void MovekoszykLeft(mojkoszyk &koszyk)
{
	koszyk.x -= koszyk.speed;
	if (koszyk.x < 40)
		koszyk.x = 40;

}

void MovekoszykRight(mojkoszyk &koszyk)
{
	koszyk.x += koszyk.speed;
	if (koszyk.x > 600)
		koszyk.x = 600;
}

void InitJablko(Jablko jabluszko[], int size)
{
	for (int i = 0; i < size; i++)
	{

		jabluszko[i].live = false;
		jabluszko[i].speed = 2;

		jabluszko[i].xx = 13;
		jabluszko[i].yy = 13;

	}
}





void DrawJablko(Jablko jabluszko[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (jabluszko[i].live)
		{
			al_draw_filled_circle(jabluszko[i].x, jabluszko[i].y, 15, al_map_rgb(255, 0, 0));
		}
	}
}
void StartJablko(Jablko jabluszko[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!jabluszko[i].live)
		{
			if (rand() % 800 == 0)
			{
				jabluszko[i].live = true;
				jabluszko[i].y = 0;
				jabluszko[i].x = 30 + rand() % (WIDTH - 30);


				break;
			}
		}
	}
}

void UpdateJablko(Jablko jabluszko[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (jabluszko[i].live)
		{
			jabluszko[i].y += jabluszko[i].speed;

			if (jabluszko[i].y > HEIGHT)
				jabluszko[i].live = false;
		}
	}
}


void EndJablko(Jablko jabluszko[], int size2, mojkoszyk &koszyk)
{
	for (int i = 0; i < size2; i++)
	{
		if (jabluszko[i].live)
		{
			if (
				jabluszko[i].x + jabluszko[i].xx > koszyk.x - koszyk.xx && jabluszko[i].x - jabluszko[i].xx < koszyk.x + koszyk.xx &&
				jabluszko[i].y - jabluszko[i].yy < koszyk.y + koszyk.yy && jabluszko[i].y + jabluszko[i].yy > koszyk.y - koszyk.yy)
			{


				jabluszko[i].live = false;
				koszyk.uratowane++;


			}

			else if (jabluszko[i].y > 375)
			{
				koszyk.stracone++;


				jabluszko[i].live = false;
			}
		}
	}
}