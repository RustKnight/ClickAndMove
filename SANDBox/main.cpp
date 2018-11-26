#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"




class Demo : public olc::PixelGameEngine
{
public:
	Demo()
	{
		sAppName = "Demo";
	}

public:
	bool OnUserCreate() override
	{
		



		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		



		return true;
	}
};






int main()
{


	Demo demo;
	if (demo.Construct(800, 600, 1, 1))
		demo.Start();

	return 0;
}