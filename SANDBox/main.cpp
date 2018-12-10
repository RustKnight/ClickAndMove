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
			addingVector.y += -1;
			addingVector.x += -1;
		}
		if (GetKey(olc::DOWN).bHeld) {
			addingVector.y += 1;
			addingVector.x += 1;
		}

		Point addedVectors = originVector + addingVector;
		Point addedVectors2 = originVector + Point{ addingVector.y, -addingVector.x };
		Point addedVectors3 = originVector + Point{ -addingVector.y, addingVector.x };

		

		DrawLine(originVector.x, originVector.y, addedVectors.x, addedVectors.y, olc::RED);
		DrawLine(originVector.x, originVector.y, addedVectors2.x, addedVectors2.y, olc::CYAN);
		DrawLine(originVector.x, originVector.y, addedVectors3.x, addedVectors3.y, olc::MAGENTA);

		return true;
	}


private:
	Point originVector{ winWidth / 2, winHeight / 2 };
	Point addingVector{ 80, 50 };//{ 80, - 50 };
	Point RightAngleCCW{ 50, -80 };
	Point RightAngleCW{ -50, 80 };
};






int main()
{


	Demo demo;
	if (demo.Construct(winWidth, winHeight, 1, 1))
		demo.Start();

	return 0;
}