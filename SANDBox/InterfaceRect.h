#pragma once
#include "olcPixelGameEngine.h"


class InterfaceRect {
public:
	InterfaceRect(olc::PixelGameEngine* ref)
		: pge {ref}
	{}
	
	void Prepare_Button(int x_in, int y_in, int w, int h, olc::Pixel col);
	void Draw_Button ();
	void Check_Click(int x_in, int y_in, int click);
	void Follow_Mouse(int x_in, int y_in);
	void Move_on_X(int xx);
	void Move_on_Y(int yy);
	
	bool Get_Status () const;
	void Monitor_Value(int& val);
	void Monitor_Value(char val);
	void Monitor_Value(std::string s);

private:
	void Change_Value(int& r);
	void Display_Value() const;

private:
	int x;
	int y;
	int width;
	int height;
	olc::Pixel color;
	olc::PixelGameEngine* pge;
	bool ready = false;
	bool follow = false;


	int* monitored_value = nullptr;
	char monitored_value_char;

	int w_dif;
	int h_dif;
};