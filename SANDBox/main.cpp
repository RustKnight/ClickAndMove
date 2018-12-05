#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Circle.h"
#include "InterfaceRect.h"
#include <ctime>

// it seems that refrences cannot be uninit. exchange them with pointers.


// Circle DRAW should be based on elapsed time TODO
class Demo : public olc::PixelGameEngine
{
public:
	Demo()
	{
		sAppName = "Demo";
	}



	bool OnUserCreate() override
	{
		
		a.Prepare_Circle(400, 300, 60, 1);
		a.Set_Segments(circle_segments);
		

		interface_red.		Prepare_Button(320, 180, 40, 20, olc::RED);
		interface_green.	Prepare_Button(380, 180, 40, 20, olc::GREEN);
		interface_blue.		Prepare_Button(440, 180, 40, 20, olc::BLUE);
		interface_progress.	Prepare_Button(380, 140, 40, 20, olc::Pixel{ 225, 75, 0 });

		vInterfaces.push_back(&interface_red);
		vInterfaces.push_back(&interface_green);
		vInterfaces.push_back(&interface_blue);
		vInterfaces.push_back(&interface_progress);

		return true;
	}



	bool OnUserUpdate(float fElapsedTime) override
	{	

		if (GetKey(olc::UP).bPressed)
		//	a.Set_Segments(circle_segments += 3);
			a.Get_ControlValue_Mod() += 10.0f;

		if (GetKey(olc::DOWN).bPressed)
		//	a.Set_Segments(circle_segments -= 3);
			a.Get_ControlValue_Mod() -= 10.0f;

		mouse_x = GetMouseX();
		mouse_y = GetMouseY();

		Clear(olc::BLACK);

		int cv = (int) a.Get_ControlValue();

		int control_mod_display = a.Get_ControlValue_Mod();
		interface_red.Monitor_Value				(control_mod_display);
		interface_green.Monitor_Value			(a.g_seg);
		interface_blue.Monitor_Value			(a.b_seg);
		interface_progress.Monitor_Value		(cv);

		if (GetKey(olc::SPACE).bPressed) 
			a.Pause_Progress();
		if (GetKey(olc::R).bPressed) 
			a.Reset_Progress();
		

		// move Button
		if (GetMouse(1).bPressed) 
			for (InterfaceRect* iR : vInterfaces)
			iR->Check_Click(mouse_x, mouse_y, 1);
			
		
		// Modify value
		if (GetMouse(0).bPressed) 
			for (InterfaceRect* iR : vInterfaces)
				iR->Check_Click(mouse_x, mouse_y, 0);


		for (InterfaceRect* iR : vInterfaces) {
			if (iR->Get_Status())
				iR->Follow_Mouse(mouse_x, mouse_y);

			iR->Draw_Button();
		}
		

 		a.Draw_Circle_Algorithm_Visible(fElapsedTime);
		//a.Highlight_Segment(mouse_x, mouse_y);

		return true;
	}


private:
	Circle a { this };
	InterfaceRect interface_red{ this };
	InterfaceRect interface_green{ this };
	InterfaceRect interface_blue{ this };
	InterfaceRect interface_progress{ this };
	std::vector <InterfaceRect*> vInterfaces;

	int circle_segments = 2;

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