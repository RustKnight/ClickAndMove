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
	void Draw_Circle_Algorithm_Visible();
	
	void Set_Segments(int n_segments);
	void Pause_Progress();
	void Reset_Progress();
	void Highlight_Segment(int x, int y);

	int& Get_Progress();

	


	int r_seg;
	int g_seg;
	int b_seg;

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
	int segment_size;
	int total_slices = -2; // -1 because first check fails to detect the first 2 points, and another -1 (total -2) because we want our first line to have the value 0
	

	int x_cen = 010;
	int y_cen = 010;
	int radius = 0;
	int segments = 0;

	

	//debug
	
	
};