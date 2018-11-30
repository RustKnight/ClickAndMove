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
	

	for (int i = 0; i <= vCircle_slices.size() -1 ; i+=2) {

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


	// it seems that CircleSegment ending point is irelevant - limit of loop can be set by progress. Thou for code clarity this should maybe 
	// be implemented another way (this meaning the seqvential draw "animation"
		for (CircleSegment cs : vCir_seg) {

			for (int i = cs.start_point; i < progress;  i += 2)
				Draw_Slice(i, cs.color);
		}

	// circle might be actually missing a last slice

		

	if (go && progress < vCircle_slices.size())
	progress += 2;


}

void Circle::Set_Segments(int seg)
{
	// circle must have values, before setting segments
	assert(ready);

	//srand(time(NULL));

	segments = seg;

	int sz;
	sz = vCircle_slices.size();  // what if it doesn't divide by 2 ? Same for below oper.
	sz /= segments;  // circ_slices size is actually divided by 2 ---- value here is the width of a segment
	if (sz % 2 == 1)
		sz += 1;

	int start = 0;
	int end = 0;

	float red	=	rand() % 255;
	float green =	rand() % 255;
	float blue	 =	rand() % 255;

	bool red_dir = rand() % 2;
	bool green_dir = rand() % 2;
	bool blue_dir = rand() % 2;

	for (int i = 0; i < segments; ++i) {
		
		color_read.push_back(col_r{ red, 'r' });
		color_read.push_back(col_r{ green, 'g' });
		color_read.push_back(col_r{ blue, 'b' });
	
		start	= end;
		end		+= sz;

		red		+= Rnd_Color	('r', red, green, blue, red_dir);
		green	+= Rnd_Color	('g', red, green, blue, green_dir);
		blue	+= Rnd_Color	('b', red, green, blue, blue_dir);

		vCir_seg.push_back(CircleSegment{ start, end, olc::Pixel{ uint8_t( red ), uint8_t( green ), uint8_t( blue ) } });

	}
}

float Circle::Rnd_Color(char c, float rd, float gr, float bl, bool direction)
{

	
	float mod;


	switch (c) {

	case 'r':	
		if (direction)
			mod = (255 - rd) / segments;
		else
			mod = -(rd / segments);

		return mod;
		break;
	

	case 'g':
		if (direction)
			mod = (255 - gr) / segments;
		else
			mod = -(gr / segments);

		return mod;
		break;


	case 'b':
		if (direction)
			mod = (255 - bl) / segments;
		else
			mod = -(bl / segments);

		return mod;
		break;

	}


}



void Circle::Pause_Progress()
{
	go = !go;
}

void Circle::Reset_Progress()
{
	progress = 0;
	Set_Segments(segments);
}


void Circle::Draw_Slice(int number, olc::Pixel col)
{
	

		assert (vCircle_slices[number].x == vCircle_slices[number + 1].x);
	
		pge->DrawLine(vCircle_slices[number].x, vCircle_slices[number].y, vCircle_slices[number + 1].x, vCircle_slices[number + 1].y, col);

	
}

