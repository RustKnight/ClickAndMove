#include "Box.h"

void Box::randomize(Point location)
{

	loc = location;
	width = 20 + rand() % 30;
	height = 20 + rand() % 30;
	color = olc::Pixel(rand() % 255, rand() % 255, rand() % 255);

}
