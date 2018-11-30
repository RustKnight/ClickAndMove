#pragma once
#include "olcPixelGameEngine.h"


struct CircleSegment {

	CircleSegment (int start, int end, olc::Pixel col)
		: start_point {start}, end_point {end}, color {col}
	{}


	int start_point;
	int end_point;
	olc::Pixel color;
};