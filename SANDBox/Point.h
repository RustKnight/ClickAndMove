#pragma once


struct Point {

	Point (int in_x, int in_y) :
		x {in_x}, y{in_y}
	{}
	Point() : x {0}, y {0} {}


	int x;
	int y;
};