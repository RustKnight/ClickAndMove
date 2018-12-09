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
		
		a.Prepare_Circle(x_center, y_center, radius, 1);
		a.Set_Segments(circle_segments);
		

		interface_red.		Prepare_Button(400 - 43, a.y_algo - 52, 40, 20, olc::RED);
	//	interface_green.	Prepare_Button(380, 180, 40, 20, olc::GREEN);
	//	interface_blue.		Prepare_Button(440, 180, 40, 20, olc::BLUE);
		interface_progress.	Prepare_Button(400 + 3, a.y_algo - 52, 40, 20, olc::Pixel{ 225, 75, 0 });
		compare_sign.		Prepare_Button(800 * 0.70f -1, y_center - radius - 15, 11, 11, olc::WHITE);
		x_axis.Prepare_Button(a.x_algo - 13, a.y_algo - 25, 27, 11, olc::WHITE);
		y_axis.Prepare_Button(a.x_algo - 39, a.y_algo - 6, 27, 11, olc::WHITE);

		vInterfaces.push_back(&interface_red);
		//vInterfaces.push_back(&interface_green);
		//vInterfaces.push_back(&interface_blue);
		vInterfaces.push_back(&interface_progress);
		vInterfaces.push_back(&compare_sign);
		vInterfaces.push_back(&x_axis);
		vInterfaces.push_back(&y_axis);

	
		stable_y_axis = a.y_algo - 11;
		stable_x_axis = a.x_algo - 11;

		// deals with displaying actual value in button
		x_offset_button = a.x_algo;
		y_offset_button = a.y_algo;

		return true;
	}



	bool OnUserUpdate(float fElapsedTime) override
	{	



		Clear(olc::BLACK);

		// starting pos for buttons
		x_axis.Move_on_X(a.x_algo - 13);
		y_axis.Move_on_Y(a.y_algo - 6);

		int current_x = a.x_algo - x_offset_button;
		int current_y = a.y_algo - y_offset_button;

		std::string str = "x: ";
		std::string str2 = "y: ";

		// line and letter

		if (a.demo_start) {
			DrawString(a.x_algo - 4, stable_y_axis, "|", olc::WHITE, 1);
			DrawString(a.x_algo - 28, stable_y_axis - 12, str, olc::YELLOW, 1);

			DrawString(stable_x_axis + 1, a.y_algo - 3, "-", olc::WHITE, 1);
			DrawString(stable_x_axis - 43, a.y_algo - 4, str2, olc::YELLOW, 1);
		}

		if (GetKey(olc::UP).bPressed)
		//	a.Set_Segments(circle_segments += 3);
			a.Get_ControlValue_Mod() += 10.0f;

		if (GetKey(olc::DOWN).bPressed)
		//	a.Set_Segments(circle_segments -= 3);
			a.Get_ControlValue_Mod() -= 10.0f;

		mouse_x = GetMouseX();
		mouse_y = GetMouseY();

		


		int cv = (int) a.Get_ControlValue();

		int control_mod_display = a.Get_ControlValue_Mod();
		interface_red.Monitor_Value				(control_mod_display);
		//interface_green.Monitor_Value			(std::string{ "---" });
		//interface_blue.Monitor_Value			(std::string{ "---" });
		interface_progress.Monitor_Value		(cv);
		compare_sign.Monitor_Value				(a.compare_rad_cath);
		x_axis.Monitor_Value					(current_x);
		y_axis.Monitor_Value					(current_y);

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
		


 		a.Draw_Circle_Algorithm_Visible (fElapsedTime);
		//a.Highlight_Segment(mouse_x, mouse_y);

		return true;
	}


private:
	Circle a { this };
	InterfaceRect interface_red{ this };
	//InterfaceRect interface_green{ this };
	//InterfaceRect interface_blue{ this };
	InterfaceRect interface_progress{ this };
	InterfaceRect compare_sign { this };
	InterfaceRect x_axis{ this };
	InterfaceRect y_axis{ this };
	std::vector <InterfaceRect*> vInterfaces;

	int circle_segments = 25;

	int mouse_x;
	int mouse_y;

	int stable_x_axis;
	int stable_y_axis;

	int x_offset_button;
	int y_offset_button;

	int radius = 80; // original size when written was 60
	int x_center = 400;
	int y_center = 300;

};






int main()
{
	

	Demo demo;
	if (demo.Construct(800, 600, 1, 1))
		demo.Start();

	return 0;
}