#include "Circle.h"
#include <assert.h>
#include <thread>
#include <math.h>



void Circle::Prepare_Circle(int in_x_cen, int in_y_cen, int in_radius, bool filled)
{
	x_cen = in_x_cen;
	y_cen = in_y_cen;
	radius = in_radius;

	x_algo = x_cen - radius + 1;
	y_algo = y_cen - radius;

	if (filled)
		Sketch_Circle_Filled();

	else
	Sketch_Circle();

	ready = true;
}

void Circle::Draw_CircleFilled()
{
	assert(ready);
	

	for (int i = 0; i < total_slices ; i++) 
		Draw_Slice(i, olc::RED);
	
}



void Circle::Sketch_Circle_Filled()
{


	for (int x = x_cen - radius; x <= (x_cen + radius); ++x) {
		for (int y = y_cen - radius; y <= (y_cen + radius); ++y) {

			int hori_cathetus = (x - x_cen) * (x - x_cen);
			int vert_cathetus = (y - y_cen) * (y - y_cen);
			int distance = hori_cathetus + vert_cathetus;

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


void Circle::Draw_Circle()
{
	assert(ready);

	for (int i = 0; i < vCircle_points.size(); ++i)
		pge->Draw(vCircle_points[i].x, vCircle_points[i].y, olc::RED);

}


void Circle::Sketch_Circle()
{
	
	// need to scale inner ring properly

	int outer_radius = radius * radius;
	int inner_radius_dif = 170;						//(radius * radius) * 0.0334f;
	

	for (int x = x_cen - radius; x <= x_cen + radius; ++x) 
		for (int y = y_cen - radius; y <= y_cen + radius; ++y) {

			int hori_cathetus = (x - x_cen) * (x - x_cen);
			int vert_cathetus = (y - y_cen) * (y - y_cen);
			int distance = hori_cathetus + vert_cathetus;
			
			
			if (distance < outer_radius && distance > outer_radius - inner_radius_dif) //120 when written
				if (y <= y_cen)
					vCircle_points.push_back(Point{ x, y });
					
		}

	// AFTER TOP HALF IS DONE, REPEAT FOR LOWER HALF

	for (int x = x_cen + radius; x >= x_cen - radius; --x)
		for (int y = y_cen + radius; y >= y_cen - radius; --y) {

			int hori_cathetus = (x - x_cen) * (x - x_cen);
			int vert_cathetus = (y - y_cen) * (y - y_cen);
			int distance = hori_cathetus + vert_cathetus;


			if (distance < outer_radius && distance > outer_radius - inner_radius_dif)
				if (y > y_cen)
					vCircle_points.push_back(Point{ x, y });
			
		}

}

void Circle::Draw_Circle_Algorithm_Visible(float fElapsedTime)
{
	using namespace std;

	assert(ready);

	// function should handle only pointer assignemnt
	if (demo_circle == nullptr)
		NewCircle();

	int radius_highlight = ((demo_circle->vCircle_points.size() / 2) / 3) * 3 - 45; // aiming for 2 o'clock-ish point
	pge->FillCircle(x_cen, y_cen, 1, olc::WHITE);

	pge->DrawString(800 * 0.70f - 50, y_cen - radius, "Radius", olc::GREEN, 1);
	pge->FillRect(800 * 0.70f, y_cen - radius, 3, 8, olc::GREEN);
	pge->DrawString(800 * 0.70f + 12, y_cen - radius, "Hypotenuse", olc::MAGENTA, 1);
	pge->FillRect(800 * 0.70f + 6, y_cen - radius, 3, 8, olc::MAGENTA);


	if (play_start_animation) {

		if ((int)control_value > 0)
			pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);

		if ((int)control_value > 1) {
			pge->DrawLine(x_cen, y_cen, demo_circle->vCircle_points[radius_highlight].x, demo_circle->vCircle_points[radius_highlight].y, olc::GREEN);

			pge->DrawString(800 * 0.70f - 50, y_cen - radius, "Radius", olc::GREEN, 1);
			pge->FillRect(800 * 0.70f, y_cen - radius, 3, radius, olc::GREEN);
		}

		if ((int)control_value > 2) {
			demo_circle->Draw_Circle_Visible(fElapsedTime);
			control_value = 3;	// hold it until circle finishes drawing

			if (demo_circle->progress > demo_circle->vCircle_points.size()) {// this means circle finished drawing
				this_thread::sleep_for(1500ms);
				control_value = 4; // give it a push
			}
		}



		if ((int)control_value > 3) {

			play_start_animation = false;
			control_value = 0; //compensate for using sleep function
		}

	}





	else {


		if (go) {

			demo_start = true;

			for (; x_algo <= x_cen + radius; ++x_algo) {
				for (; y_algo <= y_cen + radius; ++y_algo) {

					int hori_cathetus = (x_algo - x_cen) * (x_algo - x_cen);
					int vert_cathetus = (y_algo - y_cen) * (y_algo - y_cen);
					int distance = hori_cathetus + vert_cathetus;
					int comp_result = radius - sqrt(distance);

					// need to break out with each increment of x or y, need to reset control_value at end so we redraw the phases
					// maybe add break instead of x++ and add x at end

					pge->SetPixelMode(olc::Pixel::ALPHA);

					switch ((int)control_value) {

					case 0:
						if (!vDemoCircle_points.empty())
							for (Point p : vDemoCircle_points)
								pge->Draw(p.x, p.y, olc::Pixel{ 225, 75, 0 }); // orange)

						pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);
						
						pge->DrawLine(x_cen, y_cen, demo_circle->vCircle_points[radius_highlight].x, demo_circle->vCircle_points[radius_highlight].y, olc::GREEN);
						pge->DrawString(800 * 0.70f - 50, y_cen - radius, "Radius", olc::GREEN, 1);
						pge->FillRect(800 * 0.70f, y_cen - radius, 3, radius, olc::GREEN);

						// stop line blinking if going fast
						if (control_value_mod > 20)
							pge->FillRect(800 * 0.70f + 6, y_cen - radius, 3, sqrt(distance), olc::MAGENTA);
						break;

					case 1:
						if (!vDemoCircle_points.empty())
							for (Point p : vDemoCircle_points)
								pge->Draw(p.x, p.y, olc::Pixel{ 225, 75, 0 }); // orange)

						//draw horizontal cathetus
						pge->DrawLine(x_cen, y_cen, x_algo, y_cen, olc::RED);
						pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);
						
						pge->DrawLine(x_cen, y_cen, demo_circle->vCircle_points[radius_highlight].x, demo_circle->vCircle_points[radius_highlight].y, olc::GREEN);
						pge->FillRect(800 * 0.70f, y_cen - radius, 3, radius, olc::GREEN);
						
						// stop line blinking if going fast
						if (control_value_mod > 20)
							pge->FillRect(800 * 0.70f + 6, y_cen - radius, 3, sqrt(distance), olc::MAGENTA);
						break;

					case 2:
						if (!vDemoCircle_points.empty())
							for (Point p : vDemoCircle_points)
								pge->Draw(p.x, p.y, olc::Pixel{ 225, 75, 0 }); // orange)

						//draw vertical cathetus
						pge->DrawLine(x_algo, y_cen, x_algo, y_algo, olc::DARK_CYAN);
						pge->DrawLine(x_cen, y_cen, x_algo, y_cen, olc::RED);
						pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);
						
						pge->DrawLine(x_cen, y_cen, demo_circle->vCircle_points[radius_highlight].x, demo_circle->vCircle_points[radius_highlight].y, olc::GREEN);
						pge->FillRect(800 * 0.70f, y_cen - radius, 3, radius, olc::GREEN);

						// stop line blinking if going fast
						if (control_value_mod > 20)
							pge->FillRect(800 * 0.70f + 6, y_cen - radius, 3, sqrt(distance), olc::MAGENTA);
						break;

					case 3:
						if (!vDemoCircle_points.empty())
							for (Point p : vDemoCircle_points)
								pge->Draw(p.x, p.y, olc::Pixel{ 225, 75, 0 }); // orange)

						pge->DrawLine(x_algo, y_algo, x_cen, y_cen, olc::MAGENTA);
						pge->FillRect(800 * 0.70f + 6, y_cen - radius, 3, sqrt (distance), olc::MAGENTA);

						pge->DrawLine(x_algo, y_cen, x_algo, y_algo, olc::DARK_CYAN);
						pge->DrawLine(x_cen, y_cen, x_algo, y_cen, olc::RED);
						pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);
						
						pge->DrawLine(x_cen, y_cen, demo_circle->vCircle_points[radius_highlight].x, demo_circle->vCircle_points[radius_highlight].y, olc::GREEN);
						pge->FillRect(800 * 0.70f, y_cen - radius, 3, radius, olc::GREEN);
						break;

					case 4:
						if (!vDemoCircle_points.empty())
							for (Point p : vDemoCircle_points)
								pge->Draw(p.x, p.y, olc::Pixel{ 225, 75, 0 }); // orange)

						if (distance > radius * radius)
							pge->FillCircle(x_algo, y_algo, 3, olc::RED);
						else
							pge->FillCircle(x_algo, y_algo, 3, olc::GREEN);

						pge->DrawLine(x_algo, y_algo, x_cen, y_cen, olc::MAGENTA);
						pge->FillRect(800 * 0.70f + 6, y_cen - radius, 3, sqrt(distance), olc::MAGENTA);

						pge->DrawLine(x_algo, y_cen, x_algo, y_algo, olc::DARK_CYAN);
						pge->DrawLine(x_cen, y_cen, x_algo, y_cen, olc::RED);
						pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);
						
						pge->DrawLine(x_cen, y_cen, demo_circle->vCircle_points[radius_highlight].x, demo_circle->vCircle_points[radius_highlight].y, olc::GREEN);
						pge->FillRect(800 * 0.70f, y_cen - radius, 3, radius, olc::GREEN);
						break;

					case 5:
						if (!vDemoCircle_points.empty())
							for (Point p : vDemoCircle_points)
								pge->Draw(p.x, p.y, olc::Pixel{ 225, 75, 0 }); // orange)

						if (distance < radius * radius) {
							vDemoCircle_points.push_back(Point{ x_algo, y_algo });
						}
	

						if (radius < (int)sqrt(distance))
							compare_rad_cath = '<';
						else if (radius >(int)sqrt(distance))
							compare_rad_cath = '>';
						else if (radius == (int)sqrt(distance))
							compare_rad_cath = '=';
						

						pge->DrawLine(x_algo, y_algo, x_cen, y_cen, olc::MAGENTA);
						pge->FillRect(800 * 0.70f + 6, y_cen - radius, 3, sqrt(distance), olc::MAGENTA);

						pge->DrawLine(x_algo, y_cen, x_algo, y_algo, olc::DARK_CYAN);
						pge->DrawLine(x_cen, y_cen, x_algo, y_cen, olc::RED);
						pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);
						
						pge->DrawLine(x_cen, y_cen, demo_circle->vCircle_points[radius_highlight].x, demo_circle->vCircle_points[radius_highlight].y, olc::GREEN);
						pge->FillRect(800 * 0.70f, y_cen - radius, 3, radius, olc::GREEN);
						control_value = 0;
						y_algo++;// highjack for loop
						break;

					default:

						if (!vDemoCircle_points.empty())
							for (Point p : vDemoCircle_points)
								pge->Draw(p.x, p.y, olc::Pixel{ 225, 75, 0 }); // orange)

						if (distance < radius * radius)
							vDemoCircle_points.push_back(Point{ x_algo, y_algo });

						pge->DrawLine(x_algo, y_algo, x_cen, y_cen, olc::MAGENTA);
						pge->FillRect(800 * 0.70f + 6, y_cen - radius, 3, sqrt(distance), olc::MAGENTA);

						pge->DrawLine(x_algo, y_cen, x_algo, y_algo, olc::DARK_CYAN);
						pge->DrawLine(x_cen, y_cen, x_algo, y_cen, olc::RED);
						pge->DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::YELLOW);
						pge->DrawLine(x_cen, y_cen, demo_circle->vCircle_points[radius_highlight].x, demo_circle->vCircle_points[radius_highlight].y, olc::GREEN);
						pge->FillRect(800 * 0.70f, y_cen - radius, 3, radius, olc::GREEN);

						control_value = 0;
					}
					
					
					
					break; // brake so that inner loop won't increase
				}

				// check to see if nested loop still has work to do, if so block outer loop
				if (y_algo <= y_cen + radius) 
					break;
				

				else {
					y_algo = y_cen - radius;  // reset nested loop
					continue;
				}
			}

			// process ended
			if (!(x_algo <= x_cen + radius)) {
				for (Point p : vDemoCircle_points)
					pge->Draw(p.x, p.y, olc::Pixel{ 225, 75, 0 }); // orange)

				demo_ended = true;
			}
	}

}

	if (go && !demo_ended)
		control_value += fElapsedTime * (1.0f + control_value_mod);


}


void Circle::Draw_Circle_Visible(float elapsedT)
{
	assert(ready);


	for (int i = 0; i < vCircle_points.size() && i < progress; ++i)
		pge->Draw(vCircle_points[i].x, vCircle_points[i].y, olc::RED);


	// go removed for demo circle
		if (progress < vCircle_points.size() + 5)
			progress += elapsedT * 120;

}


void Circle::Draw_FilledCircle_Visiblie() {

	assert(ready);

	//draw all slices, grouped into segments - conditioned by progress and by their end point
	for (int e = 0; e < vCir_seg.size(); ++e)
		for (int i = vCir_seg[e].start_point; i < vCir_seg[e].end_point && i < progress; i++)
			Draw_Slice(i, vCir_seg[e].color);


	if (go)
		if (progress < total_slices)
			progress += 2;


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

		red		+= Rnd_Color	(red, red_dir);
		green	+= Rnd_Color	(green, green_dir);
		blue	+= Rnd_Color	(blue, blue_dir);

		vCir_seg.push_back(CircleSegment{ start, end, olc::Pixel{ uint8_t( red ), uint8_t( green ), uint8_t( blue ) } });

	}
}




float Circle::Rnd_Color(float col, bool direction)
{


	float mod;


		if (direction)
			mod = (255 - col) / segments;
		else
			mod = - (col / segments);

		return mod;
	
}


void Circle::Highlight_Segment(int x, int y)
{
	// cir_seg contains only intervals - these intervals need to be added to an offset
	int offset = x_cen - radius;


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



void Circle::NewCircle()
{

	demo_circle = new Circle{ pge };

	demo_circle->Prepare_Circle(x_cen, y_cen, radius, 0);
	
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

float& Circle::Get_Progress() 
{
	return progress;
}

float & Circle::Get_ControlValue()
{
	return control_value;

	// TODO: insert return statement here
}

float& Circle::Get_ControlValue_Mod()
{
	return control_value_mod;
}



void Circle::Draw_Slice(int number, olc::Pixel col)
{
	
	int top_point = number * 2;
	int botton_point = top_point + 1;

		assert (vCircle_slices[top_point].x == vCircle_slices[botton_point].x);
	
		pge->DrawLine(vCircle_slices[top_point].x, vCircle_slices[top_point].y, vCircle_slices[botton_point].x, vCircle_slices[botton_point].y, col);

	
}

