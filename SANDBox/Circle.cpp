#include "Circle.h"
#include <assert.h>


void Circle::Draw_CircleFilled(int in_x_cen, int in_y_cen, int in_radius)
{
	x_cen = in_x_cen;
	y_cen = in_y_cen;
	radius = in_radius;

	if (!ready)
	Sketch_Circle();

	

	for (int i = 0; i < vCircle_slices.size() - 1; ++i) {

		Draw_Slice(i, olc::RED);
	}		
}

void Circle::Draw_Circle(int in_x_cen, int in_y_cen, int in_radius)
{
	x_cen = in_x_cen;
	y_cen = in_y_cen;
	radius = in_radius;

	if (!ready)
		Sketch_Circle();

	int adjuster = 1;

	for (int i = 0; i < vCircle_slices.size(); ++i) {

		if (i + adjuster >= vCircle_slices.size())
			adjuster = 0;

		pge->Draw (vCircle_slices[i].x, vCircle_slices[i].y, olc::RED);
		pge->Draw (vCircle_slices[i + adjuster].x, vCircle_slices[i + adjuster].y, olc::RED);
	}
}



void Circle::Sketch_Circle()
{
	for (int x = x_cen - radius; x <= (x_cen + radius); ++x) {
		for (int y = y_cen - radius; y <= (y_cen + radius); ++y) {

			int a_x_sz = (x - x_cen) * (x - x_cen);
			int a_y_sz = (y - y_cen) * (y - y_cen);
			int distance = a_x_sz + a_y_sz;

			// first time in this loop when this if is true is the starting point --- // end point should be set automat. when Y loop ends, if no end point was found in the search


			if (distance < radius * radius) {
				entered = true;
				//pge->Draw(x, y, olc::RED);
			}


			// if we entered, but no longer trigger  the above if cond. - it means we are under the half of the circle
			else
				if (entered) {
					vCircle_slices.push_back({ Point{ x, y -1 } }); // end point
					entered = false;
				}


			if (entered && !starting_point) {
				vCircle_slices.push_back({ Point{ x, y } }); // start point
				starting_point = true;
			}

		}
		// reset booleans
		entered = false;
		starting_point = false;

	}

	ready = true;
}


void Circle::Draw_Circle_Visible(int in_x_cen, int in_y_cen, int in_radius)
{

	x_cen = in_x_cen;
	y_cen = in_y_cen;
	radius = in_radius;

	if (!ready)
		Sketch_Circle();

	int last_quarter_prog;

	for (int i = 0; i < progress; i+= 2) {

		last_quarter_prog  = progress - 15;

		if (i < last_quarter_prog)
			Draw_Slice(i, olc::RED);

		else
			Draw_Slice(i, olc::Pixel{ uint8_t(rand() % 255), uint8_t(rand() % 255), uint8_t(rand() % 255) });
	}

	progress++;

	//if (progress > vCircle_slices.size() + 20)
	//	progress = 0;
}


void Circle::Draw_Slice(int number, olc::Pixel col)
{
	if (number < vCircle_slices.size() - 1) {

		assert (vCircle_slices[number].x == vCircle_slices[number + 1].x);
	
		pge->DrawLine(vCircle_slices[number].x, vCircle_slices[number].y, vCircle_slices[number + 1].x, vCircle_slices[number + 1].y, col);

	}
}
