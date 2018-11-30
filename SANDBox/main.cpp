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
		a.Set_Segments(10);

		return true;
	}



	bool OnUserUpdate(float fElapsedTime) override
	{		
		Clear(olc::BLACK);

		if (GetKey(olc::SPACE).bPressed)
			a.Pause_Progress();

		if (GetKey(olc::R).bPressed)
			a.Reset_Progress();
		
		
		a.Draw_Circle_Visible ();
		


		return true;
	}


private:
	Circle a { this };
};






int main()
{
	srand(time(NULL));

	Demo demo;
	if (demo.Construct(800, 600, 1, 1))
		demo.Start();

	return 0;
}