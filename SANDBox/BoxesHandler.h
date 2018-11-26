#pragma once
#include "Box.h"
#include "Point.h"
#include "olcPixelGameEngine.h"

class BoxesHandler {

public:
	BoxesHandler (olc::PixelGameEngine* pcg_in) : pcg{ pcg_in } 
	{}

	void checkForBox(Point p);
	void dropBox();
	Box& CarriedBox();
	bool hasBox () { return carrying; }
	void throwBoxes();
	void changeBoxQuantity();
	void drawBoxes();

private:
	int number_boxes = 20;
	Box *m_aray_boxes = new Box[number_boxes];
	Box* selected_box; // would want to store instead of copy
	bool carrying = false;

	olc::PixelGameEngine* pcg;
};