#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Circle.h"
#include "InterfaceRect.h"
#include <ctime>

// it seems that refrences cannot be uninit. exchange them with pointers.

class Demo : public olc::PixelGameEngine
{
public:
	Demo()
	{
		sAppName = "Demo";
	}



	bool OnUserCreate() override
	{
		
		a.Prepare_Circle(400, 300, 50);
		a.Set_Segments(50);
		

		b1.Prepare_Button(50, 10, 40, 20, olc::GREEN);
		b2.Prepare_Button(50, 50, 40, 20, olc::RED);
		b3.Prepare_Button(50, 90, 40, 20, olc::Pixel{ 225, 75, 0 });

		return true;
	}



	bool OnUserUpdate(float fElapsedTime) override
	{	

		mouse_x = GetMouseX();
		mouse_y = GetMouseY();

		Clear(olc::BLACK);

		b1.Monitor_Value(mouse_x);
		b2.Monitor_Value(mouse_y);
		b3.Monitor_Value(a.Get_Progress());


		if (GetKey(olc::SPACE).bPressed) 
			a.Pause_Progress();
		if (GetKey(olc::R).bPressed) 
			a.Reset_Progress();
		
		if (GetMouse(1).bPressed) {
			b1.Check_Click(mouse_x, mouse_y, 1);
			b2.Check_Click(mouse_x, mouse_y, 1);
			b3.Check_Click(mouse_x, mouse_y, 1);
		}
		if (GetMouse(0).bPressed) {
			b1.Check_Click(mouse_x, mouse_y, 0);
			b2.Check_Click(mouse_x, mouse_y, 0);
			b3.Check_Click(mouse_x, mouse_y, 0);
		}


		if (b1.Get_Status())
			b1.Follow_Mouse(mouse_x, mouse_y);

		if (b2.Get_Status())
			b2.Follow_Mouse(mouse_x, mouse_y);

		if (b3.Get_Status())
			b3.Follow_Mouse(mouse_x, mouse_y);
		
		b1.Draw_Button();
		b2.Draw_Button();
		b3.Draw_Button();

		

 		a.Draw_Circle_Visible ();		 
		a.Highlight_Slice(mouse_x, mouse_y);

		return true;
	}


private:
	Circle a { this };
	InterfaceRect b1{ this };
	InterfaceRect b2{ this };
	InterfaceRect b3{ this };

	int mouse_x;
	int mouse_y;
};






int main()
{
	

	Demo demo;
	if (demo.Construct(800, 600, 1, 1))
		demo.Start();

	return 0;
}