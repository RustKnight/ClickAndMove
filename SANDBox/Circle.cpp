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
	

	for (int i = 0; i < total_slices ; i++) {

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
					vCircle_slices.push_back({ Point{ x, y } }); // end point 
					entered = false;
				}


			if (entered && !starting_point) {
				vCircle_slices.push_back({ Point{ x, y } }); // start point
				starting_point = true;
			}

		}
		
		total_slices++;
		// reset booleans
		entered = false;
		starting_point = false;

	}

}

void Circle::Draw_Circle_Algorithm_Visible()
{
	pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);


}


void Circle::Draw_Circle_Visible()
{

	assert(ready);

//	for each cer. segment draw from his start point till his end point 

		for (int e = 0; e < vCir_seg.size(); ++e)
	
			for (int i = vCir_seg[e].start_point; i < vCir_seg[e].end_point && i < progress; i++)
				Draw_Slice(i, vCir_seg[e].color);
		

	// circle might be actually missing a last slice

		
		if (go)
			if (progress < total_slices)
				progress += 1;


}



void Circle::Set_Segments(int n_segments)
{

	assert(ready);

	//srand(time(NULL));

	vCir_seg.clear();

	segments = n_segments;
	
	// one solution is to grow the circle's circumf. that way the total slices change and might fit the requaired segments
	while (total_slices % segments != 0) {
		segments++;

		if (segments > total_slices) {
			segment_size = 1;
			segments = total_slices;
			break;
		}

	}

	segment_size = total_slices / segments;

	

	//if (segment_size % 2 == 1)
	//	segment_size += 1;
	//
	//segment_size -= 2;

	int start = 0;
	int end = 0;

	float red	=	rand() % 255;
	float green =	rand() % 255;
	float blue	 =	rand() % 255;

	bool red_dir = rand() % 2;
	bool green_dir = rand() % 2;
	bool blue_dir = rand() % 2;

	for (int i = 0; i < segments; ++i) {
		
	
		start	= end;
		end		+= segment_size;

		red		+= Rnd_Color	('r', red, green, blue, red_dir);
		green	+= Rnd_Color	('g', red, green, blue, green_dir);
		blue	+= Rnd_Color	('b', red, green, blue, blue_dir);

		vCir_seg.push_back(CircleSegment{ start, end, olc::Pixel{ uint8_t( red ), uint8_t( green ), uint8_t( blue ) } });

	}
}



// highlighting slice offers nothing - a slice has no color information - better highlight circle segments and display their color
void Circle::Highlight_Segment(int x, int y)
{
	// cir_seg contains only intervals - these intervals need to be added to an offset
	int offset = x_cen - radius;


	// vCircle_slices contains slices represented as 2 points



	int seg_width = segment_size;
	int seg_height = (y_cen + radius) - (y_cen - radius);

	for (int i = 0; i < vCir_seg.size(); ++i) {

		if (x >= offset + vCir_seg[i].start_point && x < vCir_seg[i].end_point + offset && y >= y_cen - radius && y <= y_cen + radius) {
			r_seg = vCir_seg[i].color.r;
			g_seg = vCir_seg[i].color.g;
			b_seg = vCir_seg[i].color.b;


			// draw rect around circle segment
			olc::Pixel c = olc::GREEN;

			pge->DrawRect(vCir_seg[i].start_point + offset, y_cen - radius, seg_width, seg_height, c);
			c.set_alpha(80);
			pge->FillRect(vCir_seg[i].start_point + offset + 1, y_cen - radius + 1, seg_width - 1, seg_height - 1, c);
		}
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

int& Circle::Get_Progress() 
{
	return progress;
}



void Circle::Draw_Slice(int number, olc::Pixel col)
{
	
	int top_point = number * 2;
	int botton_point = top_point + 1;

		assert (vCircle_slices[top_point].x == vCircle_slices[botton_point].x);
	
		pge->DrawLine(vCircle_slices[top_point].x, vCircle_slices[top_point].y, vCircle_slices[botton_point].x, vCircle_slices[botton_point].y, col);

	
}

