#pragma once


struct Point{

	Point () {}

	Point (int in_x, int in_y):
		x {in_x}, y{in_y}
	{}



	Point operator+ (Point p1) {

		Point ret;
		ret.x = p1.x + this->x;
		ret.y = p1.y + this->y;

		return ret;
	}

	int x, y;
};