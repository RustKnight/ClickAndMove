#pragma once


struct Point {

	Point (int in_x, int in_y) :
		x {in_x}, y{in_y}
	{}
	Point() : x {0}, y {0} {}

	bool operator == (const Point& pnt) const {

		if (pnt.x == x && pnt.y == y)
			return true;
		else
			return false;
	}

	int x;
	int y;
};