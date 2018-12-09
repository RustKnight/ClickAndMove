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

	void Prepare_Circle(int in_x_cen, int in_y_cen, int in_radius, bool filled);
	
	void Draw_CircleFilled();
	void Draw_Circle();
	void Draw_Circle_Visible(float elapsedT);
	void Draw_FilledCircle_Visiblie();
	void Draw_Circle_Algorithm_Visible(float fElapsedTime);
	
	void Set_Segments(int n_segments);
	void Pause_Progress();
	void Reset_Progress();
	void Highlight_Segment(int x, int y);

	float& Get_Progress();
	float& Get_ControlValue();
	float& Get_ControlValue_Mod();
	


	int r_seg;
	int g_seg;
	int b_seg;
	char compare_rad_cath;
	int x_algo;
	int y_algo;
	bool demo_start = false;

private:
	void Sketch_Circle_Filled();
	void Sketch_Circle();
	void Draw_Slice(int number, olc::Pixel);
	float Rnd_Color(float color, bool direction);
	void NewCircle();

private:
	// maybe make a single bool that is controled by several pointers with different names : entered, left, etc.
	olc::PixelGameEngine* pge;
	bool entered = false;
	bool starting_point = false;
	bool ready = false;
	bool go = false;
	bool demo_ended = false;
	//bool not_done = true;
	std::vector<Point> vCircle_points;
	std::vector <Point> vCircle_slices;
	std::vector <CircleSegment> vCir_seg;
	std::vector <Point> vDemoCircle_points;
	float progress = 0;
	float control_value = 0;
	float control_value_mod = 0;
	bool play_start_animation = true;
	int segment_size;
	int total_slices = -2; // -1 because first check fails to detect the first 2 points, and another -1 (total -2) because we want our first line to have the value 0
	Circle* demo_circle = nullptr;

	int x_cen = 010;
	int y_cen = 010;
	int radius = 0;
	int segments = 0;

	
	


	//debug
	
	
};