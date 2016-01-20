
#pragma once
//Object IDs


struct mojkoszyk
{

	int x;
	int y;
	int speed;

	int speed2;
	int speed3;

	int lives;
	int xx;
	int yy;

	int uratowane;
	int stracone;

	ALLEGRO_BITMAP *image;

};

struct Jablko
{

	int x;
	int y;
	bool live;
	int speed;

	int xx;
	int yy;

	ALLEGRO_BITMAP *image;
};

struct Tlo
{
	float x;
	float y;
	float speed;
	int dirX;
	int width;
	int height;

	ALLEGRO_BITMAP *image;
};