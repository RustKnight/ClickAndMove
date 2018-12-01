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
	olc::Pixel shade = color;
	shade.set_alpha(45);
	pge->SetPixelMode(olc::Pixel::ALPHA);

	pge->FillRect(x + 1, y + 1, width - 1, height - 1, shade);

	Display_Value();
}

void InterfaceRect::Check_Click(int x_in, int y_in, int click)
{
	if (click == 1) {
		if (x_in >= x && x_in <= x + width && y_in >= y && y_in <= y + height)
			follow = !follow;

		w_dif = x_in - x;
		h_dif = y_in - y;
	}

	if (click == 0) {
		if (x_in >= x && x_in <= x + width && y_in >= y && y_in <= y + height)
			Change_Value();
	}
}

void InterfaceRect::Follow_Mouse(int x_in, int y_in)
{
	

	x = x_in - w_dif;
	y = y_in - h_dif;

}

void InterfaceRect::Change_Value()
{
	std::cin >> stored_value;
}

bool InterfaceRect::Get_Status() const
{
	return follow;
}

void InterfaceRect::Monitor_Value(int val)
{
	stored_value = val;

}

void InterfaceRect::Display_Value() const
{

	std::string s = std::to_string(stored_value);
	int size = s.size();


	pge->DrawString((x + width/2) - size * 4, y + height/4, s);
}
