#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Box.h"
#include "Point.h"
#include <ctime>

int window_width = 800;
int window_height = 600;


class Demo : public olc::PixelGameEngine
{
public:
	Demo() :
		m_box1 {Point {rand() % 750, rand() % 550 }, olc::Pixel(rand() % 255, rand() % 255, rand() % 255) }
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

		



		return true;
	}


private:
	Box m_box1;
};






int main()
{

	srand(time(NULL));

	Demo demo;
	if (demo.Construct(window_width, window_height, 1, 1))
		demo.Start();

	return 0;
}