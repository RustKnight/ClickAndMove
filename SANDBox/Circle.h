#pragma once
#include "olcPixelGameEngine.h"
#include "Point.h"
#include <vector>

class Circle {

public:
	Circle (olc::PixelGameEngine* ref) :
		pge {ref}
	{}


	void Draw_CircleFilled(int in_x_cen, int in_y_cen, int in_radius);
	void Draw_Circle(int in_x_cen, int in_y_cen, int in_radius);
	void Draw_Circle_Visible(int in_x_cen, int in_y_cen, int in_radius);
	void Pause_Progress();

private:
	void Sketch_Circle();
	void Draw_Slice(int number, olc::Pixel);
	// might need a refreh/clear method

private:
	// maybe make a single bool that is controled by several pointers with different names : entered, left, etc.
	olc::PixelGameEngine* pge;
	bool entered = false;
	bool starting_point = false;
	bool ready = false;
	bool green = false;
	std::vector <Point> vCircle_slices;
	int progress = 0;

	int x_cen;
	int y_cen;
	int radius;
};