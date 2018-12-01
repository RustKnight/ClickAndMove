#pragma once
#include "olcPixelGameEngine.h"


class InterfaceRect {
public:
	InterfaceRect(olc::PixelGameEngine* ref)
		: pge {ref}
	{}
	
	void Prepare_Button(int xx, int yy, int w, int h, olc::Pixel col);
	void Draw_Button ();


private:
	int x;
	int y;
	int width;
	int height;
	olc::Pixel color;
	olc::PixelGameEngine* pge;
	bool ready = false;
};