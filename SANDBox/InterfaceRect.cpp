#include "InterfaceRect.h"
#include <assert.h>

void InterfaceRect::Prepare_Button(int xx, int yy, int w, int h, olc::Pixel col)
{
	x = xx;
	y = yy;
	width = w;
	height = h;
	color = col;
	ready = true;
}

void InterfaceRect::Draw_Button()
{
	assert(ready);

	pge->DrawRect(x, y, width, height, color);


	pge->FillRect(x + 1, y + 1, width - 1, height - 1, olc::RED);

}

void InterfaceRect::Check_Click(int x_in, int y_in)
{
	if (x_in >= x && x_in <= x + width && y_in >= y && y_in <= y + height)
		follow = !follow;

	w_dif = x_in - x;
	h_dif = y_in - y;
}

void InterfaceRect::Follow_Mouse(int x_in, int y_in)
{
	

	x = x_in - w_dif;
	y = y_in - h_dif;

}

bool InterfaceRect::Get_Status() const
{


	return follow;
}
