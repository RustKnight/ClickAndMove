#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Circle.h"



class Demo : public olc::PixelGameEngine
{
public:
	Demo()
	{
		sAppName = "Demo";
	}



	bool OnUserCreate() override
	{
		



		return true;
	}



	bool OnUserUpdate(float fElapsedTime) override
	{		
		Clear(olc::BLACK);

		if (GetKey(olc::SPACE).bPressed)
			go = !go;

		if (go)
		a.Draw_Circle_Visible(400,300, 100);


		return true;
	}


private:
	Circle a { this };
	bool go = false;
};






int main()
{


	Demo demo;
	if (demo.Construct(800, 600, 1, 1))
		demo.Start();

	return 0;
}