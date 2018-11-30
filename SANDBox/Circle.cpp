#include "Circle.h"
#include <assert.h>


void Circle::Prepare_Circle(int in_x_cen, int in_y_cen, int in_radius)
{
	x_cen = in_x_cen;
	y_cen = in_y_cen;
	radius = in_radius;

	Sketch_Circle();

	ready = true;
}

void Circle::Draw_CircleFilled()
{
	assert(ready);
	

	for (int i = 0; i < vCircle_slices.size() - 1; ++i) {

		Draw_Slice(i, olc::RED);
	}		
}

void Circle::Draw_Circle()
{
	assert(ready);

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

}


void Circle::Draw_Circle_Visible()
{

	assert(ready);

	//int III_slice;
	//int II_slice;
	//int I_slice;
	//
	//for (int i = 0; i < progress; i+= 2) {

		for (CircleSegment cs : vCir_seg) {

			for (int i = cs.start_point; i <= cs.end_point;  i += 2)
				Draw_Slice(i, cs.color);
		}

		//draw last missing slice
		Draw_Slice(vCircle_slices.size()-2, vCir_seg[vCir_seg.size()-1].color);

		//III_slice	= progress - 15;
		//II_slice	= progress - 30;
		//I_slice		= progress - 45;
		//
		//
		//if (i <= I_slice)
		//	Draw_Slice(i, olc::RED);
		//
		//else if ( i <= II_slice)
		//	Draw_Slice(i, olc::Pixel{ 191, 0, 0 });
		//
		//else if (i <= III_slice)
		//	Draw_Slice(i, olc::Pixel{ 127, 0, 0 });
		//
		//else if (i >= III_slice)
		//	Draw_Slice(i, olc::Pixel{ 63, 0, 0 });


		//RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
//	}

	//olc::Pixel{ uint8_t(rand() % 255), uint8_t(rand() % 255), uint8_t(rand() % 255) }
	if (green)
	progress++;


}

void Circle::Set_Segments(int seg)
{
	// circle must have values, before setting segments
	assert(ready);

	segments = seg;

	int sz;
	sz = vCircle_slices.size();  // what if it doesn't divide by 2 ? Same for below oper.
	sz /= segments;  // circ_slices size is actually divided by 2 ---- value here is the width of a segment
	if (sz % 2 == 1)
		sz += 1;

	int start = 0;
	int end = 0;

	for (int i = 0; i < segments; ++i) {
		
	
		start = end;
		end += sz;

		vCir_seg.push_back(CircleSegment{ start, end, olc::Pixel{ uint8_t(rand() % 255), uint8_t(rand() % 255), uint8_t(rand() % 255) } });
	}
}

void Circle::Pause_Progress()
{
	green = !green;
}

void Circle::Reset_Progress()
{
	progress = 0;
}


void Circle::Draw_Slice(int number, olc::Pixel col)
{
	if (number < vCircle_slices.size() - 1) {

		assert (vCircle_slices[number].x == vCircle_slices[number + 1].x);
	
		pge->DrawLine(vCircle_slices[number].x, vCircle_slices[number].y, vCircle_slices[number + 1].x, vCircle_slices[number + 1].y, col);

	}
}
