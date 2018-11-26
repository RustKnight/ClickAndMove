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
		m_box1{ Point {rand() % 750, rand() % 550 } }
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


		if (GetMouse(2).bPressed)
			m_box1.randomize(Point{ rand() % 750, rand() % 550 });


		FillRect(
			m_box1.get_loc().x,
			m_box1.get_loc().y,
			m_box1.get_width(),
			m_box1.get_height(),
			m_box1.get_col());



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