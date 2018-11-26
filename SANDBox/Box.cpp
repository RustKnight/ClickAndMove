#include "Box.h"

void Box::randomize(Point location)
{

	loc = location;
	width = 20 + rand() % 30;
	height = 20 + rand() % 30;
	color = olc::Pixel(rand() % 255, rand() % 255, rand() % 255);
	selected = false;

}

void Box::tag_attempt(Point location)
{

	if (location.x > loc.x && location.x < loc.x + width)
		if (location.y > loc.y && location.y < loc.y + height)
			if (selected)
				selected = false;
			else {
				selected = true;
				width_dif = loc.x - location.x;
				height_dif = loc.y - location.y;
			}
	

}

void Box::follow_mouse(Point location)
{

	loc.x = location.x + width_dif;
	loc.y = location.y + height_dif;

}

void Box::swap_sizes()
{
	int z = width;
	width = height;
	height = z;
}

void Box::deselect()
{
	selected = false;
}
