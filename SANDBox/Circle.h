#pragma once
#include "olcPixelGameEngine.h"
#include "Point.h"
#include "CircleSegment.h"
#include <vector>

class Circle {

public:
	Circle (olc::PixelGameEngine* ref) :
		pge {ref}
	{}

	void Prepare_Circle(int in_x_cen, int in_y_cen, int in_radius);
	void Draw_CircleFilled();
	void Draw_Circle();
	void Draw_Circle_Visible();
	void Set_Segments(int seg);
	void Pause_Progress();
	void Reset_Progress();

	//int Get_Segment (int x, int y)

private:
	void Sketch_Circle();
	void Draw_Slice(int number, olc::Pixel);
	float Rnd_Color(char c, float r, float g, float b, bool direction);
	// might need a refreh/clear method

private:
	// maybe make a single bool that is controled by several pointers with different names : entered, left, etc.
	olc::PixelGameEngine* pge;
	bool entered = false;
	bool starting_point = false;
	bool ready = false;
	bool go = false;
	std::vector <Point> vCircle_slices;
	std::vector <CircleSegment> vCir_seg;
	int progress = 0;

	int x_cen = 010;
	int y_cen = 010;
	int radius = 0;
	int segments = 0;

	//debug
	
	std::vector<col_r> color_read;
};