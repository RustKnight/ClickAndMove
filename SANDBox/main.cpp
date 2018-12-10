#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Point.h"

int winWidth = 800;
int winHeight = 600;


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
		Clear(olc::BLACK);

		if (GetKey(olc::UP).bHeld) {
			scale_vector_by_factor += 0.01f;
		}
		if (GetKey(olc::DOWN).bHeld) {
			scale_vector_by_factor -= 0.01f;
		}


		DrawCircle	(CircleCenter.x, CircleCenter.y, radius, olc::WHITE);
		DrawRect	(CircleCenter.x - radius, CircleCenter.y - radius, radius*2, radius*2, olc::WHITE);
		DrawLine	(CircleCenter.x, CircleCenter.y, GetMouseX(), GetMouseY(), olc::WHITE);

		int mouse_vector_x = GetMouseX() - CircleCenter.x;
		int mouse_vector_y = GetMouseY() - CircleCenter.y;

		//DrawLine (CircleCenter.x, CircleCenter.y, )

		//Draw vector x and y componets
		DrawLine(CircleCenter.x, CircleCenter.y, CircleCenter.x + mouse_vector_x * scale_vector_by_factor, CircleCenter.y, olc::RED);
		DrawLine(CircleCenter.x + mouse_vector_x * scale_vector_by_factor, CircleCenter.y, CircleCenter.x + mouse_vector_x * scale_vector_by_factor, CircleCenter.y + mouse_vector_y * scale_vector_by_factor, olc::BLUE);
	
		//draw the point of interest
		FillCircle(CircleCenter.x + mouse_vector_x * scale_vector_by_factor, CircleCenter.y + mouse_vector_y * scale_vector_by_factor, 3, olc::GREEN);

		//vector from the difference between mouse vector and point of interest
		Point interest{ int(GetMouseX() - (CircleCenter.x + mouse_vector_x * scale_vector_by_factor)), int((CircleCenter.y + mouse_vector_y * scale_vector_by_factor) - GetMouseY()) };

		DrawLine(CircleCenter.x + mouse_vector_x * scale_vector_by_factor,  
				CircleCenter.y + mouse_vector_y * scale_vector_by_factor, 
				interest.y + CircleCenter.y + mouse_vector_y * scale_vector_by_factor,
				interest.x + CircleCenter.x + mouse_vector_x * scale_vector_by_factor, olc::MAGENTA);
		//DrawLine(CircleCenter.x + mouse_vector_x * scale_vector_by_factor, CircleCenter.y + mouse_vector_y * scale_vector_by_factor, -interest.y, interest.x, olc::WHITE);


		return true;
	}


private:
	Point CircleCenter{ winWidth / 2, winHeight / 2 };
	int radius = 60;
	float scale_vector_by_factor = 0.0f;
	//Point originVector{ winWidth / 2, winHeight / 2 };
	//Point addingVector{ 80, 50 };//{ 80, - 50 };
	//Point RightAngleCCW{ 50, -80 };
	//Point RightAngleCW{ -50, 80 };
};






int main()
{


	Demo demo;
	if (demo.Construct(winWidth, winHeight, 1, 1))
		demo.Start();

	return 0;
}