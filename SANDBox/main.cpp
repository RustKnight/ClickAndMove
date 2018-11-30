#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Circle.h"
#include <ctime>



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

		b.Prepare_Circle(400, 100, 50);
		b.Set_Segments(50);

		c.Prepare_Circle(200, 200, 50);
		c.Set_Segments(50);

		d.Prepare_Circle(600, 200, 50);
		d.Set_Segments(50);

		return true;
	}



	bool OnUserUpdate(float fElapsedTime) override
	{	

		mouse_x = GetMouseX();
		mouse_y = GetMouseY();

		Clear(olc::BLACK);

		if (GetKey(olc::SPACE).bPressed) {
			a.Pause_Progress();
			b.Pause_Progress();
			c.Pause_Progress();
			d.Pause_Progress();
		}

		if (GetKey(olc::R).bPressed) {
			a.Reset_Progress();
			b.Reset_Progress();
			c.Reset_Progress();
			d.Reset_Progress();
		}
		
		
		//FillCircle(400, 300, 50, olc::RED);
 		a.Draw_Circle_Visible ();
		b.Draw_Circle_Visible();
		c.Draw_Circle_Visible();
		d.Draw_Circle_Visible();
		 
		b.Highlight_Slice(mouse_x, mouse_y);

		return true;
	}


private:
	Circle a { this };
	Circle b { this };
	Circle c { this };
	Circle d { this };

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