#pragma once
#include "Point.h"
#include "olcPixelGameEngine.h"



class Box {
public:
	Box(Point loc_in, olc::Pixel col) :
		width{ 20 + rand() % 30 }, height{ 20 + rand() % 30 },  loc {loc_in}, color{ col }, selected {false}
	{}

//Getters
	int get_width() const { return width; }
	int get_height() const { return height; }

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