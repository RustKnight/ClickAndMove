#pragma once
#include "Point.h"

struct Mouse {


	void update_loc(Point p) { location = p; }


	Point location;
};