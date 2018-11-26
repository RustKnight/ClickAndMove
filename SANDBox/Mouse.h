#pragma once
#include "Point.h"

struct Mouse {


	void update_loc(Point p) { location = p; }


	bool carrying = false;
	Point location;
};