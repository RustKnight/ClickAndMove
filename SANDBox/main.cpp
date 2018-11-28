#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"




class Demo : public olc::PixelGameEngine
{
public:
	Demo()
	{
		sAppName = "Demo";
	}

	void Draw_Circle(int x_cen, int y_cen, int radius)
	{
		DrawRect(x_cen - radius, y_cen - radius, radius * 2, radius * 2, olc::BLUE);

		for (int x = x_cen - radius; x <= (x_cen + radius); ++x)
			for (int y = y_cen - radius; y <= (y_cen + radius); ++y) {

				int a_x_sz = (x - x_cen) * (x - x_cen);
				int a_y_sz = (y - y_cen) * (y - y_cen);
				int distance = a_x_sz + a_y_sz;

				if (distance < radius * radius + ctrl)
					Draw(x, y, olc::RED);

			}

		
	}

public:
	bool OnUserCreate() override
	{
		



		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		if (GetKey(olc::Q).bHeld)
			ctrl+= 20;

		if (GetKey(olc::A).bHeld)
			ctrl-= 20;

		
		Clear(olc::GREY);

		//FillCircle(400, 300, 100, olc::BLUE);
		Draw_Circle(400, 300, 100);


		return true;
	}


	int ctrl = 0;
};






int main()
{


	Demo demo;
	if (demo.Construct(800, 600, 1, 1))
		demo.Start();

	return 0;
}