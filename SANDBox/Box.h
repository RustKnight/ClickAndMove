#pragma once
#include "Point.h"
#include "olcPixelGameEngine.h"



class Box {
public:
	Box(Point loc_in) :
		width{ 20 + rand() % 30 }, height{ 20 + rand() % 30 },  loc {loc_in}, color{ olc::Pixel(rand() % 255, rand() % 255, rand() % 255) }, selected {false}
	{}

	Box() { randomize(Point{ rand() % 750, rand() % 550 }); }

	void randomize(Point location);

//Getters
	int get_width() const { return width; }
	int get_height() const { return height; }
	Point get_loc() const { return loc; }
	olc::Pixel get_col() const { return color; }

//Methods
private:

//Data members
private:
	int width;
	int height;
	Point loc;
	olc::Pixel color;
	bool selected;
};