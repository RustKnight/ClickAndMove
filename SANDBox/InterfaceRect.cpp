#include "InterfaceRect.h"
#include <assert.h>
#include <sstream>

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
			Change_Value(*monitored_value);
	}
}

void InterfaceRect::Follow_Mouse(int x_in, int y_in)
{
	

	x = x_in - w_dif;
	y = y_in - h_dif;

}

void InterfaceRect::Move_on_X(int xx)
{
	x = xx;
}

void InterfaceRect::Move_on_Y(int yy)
{
	y = yy;
}

void InterfaceRect::Change_Value(int& r)
{
	
/*
	while (1) {

		if (pge->GetKey(olc::SPACE).bPressed)
			break;

		if		(pge->GetKey(olc::K1).bPressed)
			s += "1";

		else if (pge->GetKey(olc::K2).bPressed)
			s += "2";

		else if (pge->GetKey(olc::K3).bPressed)
			s += "3";

		else if (pge->GetKey(olc::K4).bPressed)
			s += "4";

		else if (pge->GetKey(olc::K5).bPressed)
			s += "5";

		else if (pge->GetKey(olc::K6).bPressed)
			s += "6";

		else if (pge->GetKey(olc::K7).bPressed)
			s += "7";

		else if (pge->GetKey(olc::K8).bPressed)
			s += "8";

		else if (pge->GetKey(olc::K9).bPressed)
			s += "9";

		else if (pge->GetKey(olc::K0).bPressed)
			s += "0";
	}


	int num = std::stoi(s);

	*/

	std::cin >> *monitored_value;
}

bool InterfaceRect::Get_Status() const
{
	return follow;
}

void InterfaceRect::Monitor_Value(int& val)
{
	monitored_value = &val;
}

void InterfaceRect::Monitor_Value(char val)
{
	monitored_value_char = val;
}

void InterfaceRect::Monitor_Value(std::string s) {

	int size = s.size();
	
	if (s == "---")
		pge->DrawString((x + width / 2) - size * 4 + 2, y + height / 3, s, olc::WHITE, 1);

	else
	pge->DrawString((x + width / 2) - size * 4 + 2, y + height / 3, s, olc::YELLOW, 1);

}

void InterfaceRect::Display_Value() const
{
	if (monitored_value != nullptr) {
		std::string s = std::to_string(*monitored_value);
		int size = s.size();


		pge->DrawString((x + width / 2) - size * 4 + 1, y + height / 3, s);
	}

	else {

		std::stringstream ss;
		std::string s;
		char c = monitored_value_char;
		ss << c;
		ss >> s;
		int size = s.size();

		
		pge->DrawString((x + width / 2) - size * 4 + 2, y + height / 3, s, olc::YELLOW, 1);

	}

}
