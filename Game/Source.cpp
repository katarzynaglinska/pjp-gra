#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "objects.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>


const int WIDTH = 640;
const int HEIGHT = 480;
const int Jablko_num = 7;
const int Jablko_num2 = 3;
enum KEYS { LEFT, RIGHT, ENTER };
bool keys[3] = { false, false, false };
int licz = 0;
enum EKRAN { MENU, GRA, KONIEC };

mojkoszyk koszyk;
Jablko jabluszko[Jablko_num];
Jablko jabluszko_zle[Jablko_num2];

void Initkoszyk(mojkoszyk &koszyk, ALLEGRO_BITMAP *image);
void Drawkoszyk(mojkoszyk &koszyk);
void MovekoszykLeft(mojkoszyk &koszyk);
void MovekoszykRight(mojkoszyk &koszyk);


void InitJablko(Jablko jabluszko[], int size, ALLEGRO_BITMAP *image);
void InitJablko2(Jablko jabluszko[], int size, mojkoszyk &koszyk);
void InitJablko3(Jablko jabluszko[], int size, mojkoszyk &koszyk);
void DrawJablko(Jablko jabluszko[], int size);
void StartJablko(Jablko jabluszko[], int size);
void UpdateJablko(Jablko jabluszko[], int size);

void InitJablko_zle(Jablko jabluszko_zle[], int size, ALLEGRO_BITMAP *image);
void DrawJablko_zle(Jablko jabluszko_zle[], int size);
void StartJablko_zle(Jablko jabluszko_zle[], int size);
void UpdateJablko_zle(Jablko jabluszko_zle[], int size);

void EndJablko(Jablko jabluszko[], int size2, mojkoszyk &koszyk);
void EndJablko_zle(Jablko jabluszko_zle[], int size2, mojkoszyk &koszyk);

void StartTlo(Tlo &back, float x, float y, float speed, int width, int height, int dirX, ALLEGRO_BITMAP *image);
void UpdateTlo(Tlo &back);
void DrawTlo(Tlo &back);

void ZamianaEkranu(int &obecne, int nowe);

int main(void)
{
	srand(time(NULL));

	//primitive variable
	const int FPS = 60;
	bool done = false;
	bool redraw = true;
	int imagewidth = 0;
	int imageheight = 0;
	int obecne = -1;

	Tlo background;

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_BITMAP *image = NULL;
	ALLEGRO_BITMAP *image2 = NULL;
	ALLEGRO_BITMAP *image3 = NULL;
	ALLEGRO_BITMAP *obrazekmenu = NULL;
	ALLEGRO_BITMAP *obrazekkon = NULL;
	ALLEGRO_BITMAP *obrazekjablka = NULL;
	ALLEGRO_BITMAP *obrazekkosza = NULL;
	ALLEGRO_BITMAP *obrazekjablka_zle = NULL;
	ALLEGRO_BITMAP *bgImage = NULL;


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
	al_init_image_addon();


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);



	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	font = al_load_font("font.ttf", 22, 0);
	image = al_load_bitmap("serce1.jpg");
	image2 = al_load_bitmap("serce1.jpg");
	image3 = al_load_bitmap("serce1.jpg");
	obrazekmenu = al_load_bitmap("menu.png");
	obrazekkon = al_load_bitmap("koniec2.png");
	obrazekkosza = al_load_bitmap("kosz.png");
	obrazekjablka = al_load_bitmap("jablko.png");
	obrazekjablka_zle = al_load_bitmap("jablkozle.png");
	bgImage = al_load_bitmap("tlo.png");

	ZamianaEkranu(obecne, MENU);

	Initkoszyk(koszyk, obrazekkosza);
	InitJablko(jabluszko, Jablko_num, obrazekjablka);
	InitJablko_zle(jabluszko_zle, Jablko_num2, obrazekjablka_zle);
	StartTlo(background, 0, 0, 1, 1040, 480, -1, bgImage);

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

			if (obecne == MENU)
			{
			}

			else if (obecne == GRA)
			{
				UpdateTlo(background);

				StartJablko(jabluszko, Jablko_num);
				UpdateJablko(jabluszko, Jablko_num);

				StartJablko_zle(jabluszko_zle, Jablko_num2);
				UpdateJablko_zle(jabluszko_zle, Jablko_num2);

				EndJablko(jabluszko, Jablko_num, koszyk);
				EndJablko_zle(jabluszko_zle, Jablko_num2, koszyk);


				if (koszyk.lives <= 0)
					ZamianaEkranu(obecne, KONIEC);
			}

			else if (obecne == KONIEC)
			{
			}
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
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


			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = true;
				if (obecne == MENU)
					ZamianaEkranu(obecne, GRA);
				else if (obecne == KONIEC)
					ZamianaEkranu(obecne, GRA);
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

			if (obecne == MENU)
			{
				al_draw_bitmap(obrazekmenu, 0, 0, 0);
			}
			else if (obecne == GRA)
			{
				DrawTlo(background);
				Drawkoszyk(koszyk);
				DrawJablko(jabluszko, Jablko_num);
				DrawJablko_zle(jabluszko_zle, Jablko_num2);


				al_draw_textf(font, al_map_rgb(255, 0, 255), 20, HEIGHT - 40, 0, "  URATOWANE  %i ", koszyk.uratowane);
				al_draw_textf(font, al_map_rgb(255, 0, 255), WIDTH - 160, HEIGHT - 40, 0, "  STRACONE  %i ", koszyk.stracone);

				licz = licz + 1;

				al_draw_textf(font, al_map_rgb(255, 255, 255), 0.1*WIDTH, 0.05*HEIGHT, ALLEGRO_ALIGN_CENTRE,
					"czas: %i", licz / 60);

				if (licz >= 900 && licz <= 1260) {
					al_draw_textf(font, al_map_rgb(255, 255, 255), 0.5*WIDTH, 0.4*HEIGHT, ALLEGRO_ALIGN_CENTRE, "runda 2");
				}
				if (licz == 900) InitJablko2(jabluszko, Jablko_num, koszyk);

				if (licz >= 1800 && licz <= 2160) {
					al_draw_textf(font, al_map_rgb(255, 255, 255), 0.5*WIDTH, 0.4*HEIGHT, ALLEGRO_ALIGN_CENTRE, "runda 3");
				}
				if (licz == 1800) InitJablko3(jabluszko, Jablko_num, koszyk);

				if (koszyk.lives == 3)al_draw_bitmap(image, WIDTH / 2 - 40, HEIGHT - 40, 0);
				if (koszyk.lives == 3 || koszyk.lives == 2)al_draw_bitmap(image2, WIDTH / 2, HEIGHT - 40, 0);
				if (koszyk.lives == 3 || koszyk.lives == 2 || koszyk.lives == 1)al_draw_bitmap(image3, WIDTH / 2 + 40, HEIGHT - 40, 0);

			}

			else if (obecne == KONIEC)
			{
				licz = 0;
				al_draw_bitmap(obrazekkon, 0, 0, 0);
				al_draw_textf(font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 40, ALLEGRO_ALIGN_CENTRE, " KONIEC GRY. ");
				al_draw_textf(font, al_map_rgb(0, 0, 0), WIDTH / 2 - 5, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Aby zagrac ponownie wcisnij ENTER. ");
			}


			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(obrazekjablka_zle);
	al_destroy_bitmap(obrazekkosza);
	al_destroy_bitmap(obrazekjablka);
	al_destroy_bitmap(obrazekmenu);
	al_destroy_bitmap(obrazekkon);
	al_destroy_bitmap(image);
	al_destroy_bitmap(image2);
	al_destroy_bitmap(image3);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);
	al_destroy_display(display);



	return 0;
}




void Initkoszyk(mojkoszyk &koszyk, ALLEGRO_BITMAP *image)
{
	koszyk.x = 320;
	koszyk.y = 340;
	koszyk.speed = 5;
	koszyk.lives = 3;

	koszyk.xx = 40;
	koszyk.yy = 7;
	koszyk.uratowane = 0;
	koszyk.stracone = 0;

	if (image != NULL)
		koszyk.image = image;
}
void Drawkoszyk(mojkoszyk &koszyk)
{
	al_draw_bitmap(koszyk.image, koszyk.x, koszyk.y, 0);
	//al_draw_filled_rectangle(koszyk.x - 40, koszyk.y - 2, koszyk.x + 40, koszyk.y + 30, al_map_rgb(150, 75, 0));
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

void InitJablko(Jablko jabluszko[], int size, ALLEGRO_BITMAP *image)
{

	for (int i = 0; i < size; i++)
	{

		jabluszko[i].live = false;
		jabluszko[i].speed = 2;

		jabluszko[i].xx = 13;
		jabluszko[i].yy = 13;

		if (image != NULL)
			jabluszko[i].image = image;
	}

}

void InitJablko_zle(Jablko jabluszko_zle[], int size, ALLEGRO_BITMAP *image)
{

	for (int i = 0; i < size; i++)
	{

		jabluszko_zle[i].live = false;
		jabluszko_zle[i].speed = 2;

		jabluszko_zle[i].xx = 13;
		jabluszko_zle[i].yy = 13;

		if (image != NULL)
			jabluszko_zle[i].image = image;
	}

}

void InitJablko2(Jablko jabluszko[], int size, mojkoszyk &koszyk)
{

	for (int i = 0; i < size; i++)
	{
		jabluszko[i].live = false;
		jabluszko[i].speed = 4;
		koszyk.speed = 6;

		jabluszko[i].xx = 13;
		jabluszko[i].yy = 13;

	}

}

void InitJablko3(Jablko jabluszko[], int size, mojkoszyk &koszyk)
{
	for (int i = 0; i < size; i++)
	{

		jabluszko[i].live = false;
		jabluszko[i].speed = 6;
		koszyk.speed = 7;

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
			al_draw_bitmap(jabluszko[i].image, jabluszko[i].x, jabluszko[i].y, 0);
		//	al_draw_filled_circle(jabluszko[i].x, jabluszko[i].y, 15, al_map_rgb(255, 0, 0));
		}
	}
}


void DrawJablko_zle(Jablko jabluszko_zle[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (jabluszko_zle[i].live)
		{
			al_draw_bitmap(jabluszko_zle[i].image, jabluszko_zle[i].x, jabluszko_zle[i].y, 0);
			//al_draw_filled_circle(jabluszko_zle[i].x, jabluszko_zle[i].y, 15, al_map_rgb(0, 255, 0));
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

void StartJablko_zle(Jablko jabluszko_zle[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!jabluszko_zle[i].live)
		{
			if (rand() % 800 == 0)
			{
				jabluszko_zle[i].live = true;
				jabluszko_zle[i].y = 0;
				jabluszko_zle[i].x = 30 + rand() % (WIDTH - 30);


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


void UpdateJablko_zle(Jablko jabluszko[], int size)
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



void EndJablko_zle(Jablko jabluszko_zle[], int size2, mojkoszyk &koszyk)
{
	for (int i = 0; i < size2; i++)
	{
		if (jabluszko_zle[i].live)
		{
			if (
				jabluszko_zle[i].x + jabluszko_zle[i].xx > koszyk.x - koszyk.xx && jabluszko_zle[i].x - jabluszko_zle[i].xx < koszyk.x + koszyk.xx &&
				jabluszko_zle[i].y - jabluszko_zle[i].yy < koszyk.y + koszyk.yy && jabluszko_zle[i].y + jabluszko_zle[i].yy > koszyk.y - koszyk.yy)
			{

				jabluszko_zle[i].live = false;
				koszyk.lives--;

			}

			else if (jabluszko_zle[i].y > 375)
			{

				jabluszko_zle[i].live = false;
			}
		}
	}
}



void ZamianaEkranu(int &obecne, int nowe)
{
	if (obecne == MENU)
	{
	}
	else if (obecne == GRA)
	{
	}
	else if (obecne == KONIEC)
	{
	}

	obecne = nowe;

	if (obecne == MENU)
	{
	}
	else if (obecne == GRA)
	{
		Initkoszyk(koszyk, NULL);
		InitJablko(jabluszko, Jablko_num, NULL);
		InitJablko_zle(jabluszko_zle, Jablko_num2, NULL);
	}
	else if (obecne == KONIEC)
	{
	}
}

void StartTlo(Tlo &back, float x, float y, float speed, int width, int height, int dirX, ALLEGRO_BITMAP *image)
{
	back.x = x;
	back.y = y;
	back.speed = speed;
	back.width = width;
	back.height = height;
	back.dirX = dirX;
	back.image = image;
}

void UpdateTlo(Tlo &back)
{
	back.x += back.speed * back.dirX;
	if (back.x + back.width <= 0)
		back.x = 0;
}

void DrawTlo(Tlo &back)
{
	al_draw_bitmap(back.image, back.x, back.y, 0);

	if (back.x + back.width < WIDTH)
		al_draw_bitmap(back.image, back.x + back.width, back.y, 0);
}
