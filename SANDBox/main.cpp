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
			for (int i = 0; i < number_boxes; i++)
				m_aray_boxes[i].randomize(Point{ rand() % 750, rand() % 550 });

		if (GetKey(olc::SPACE).bPressed) {
			std::cout << "Enter value: " << std::endl;
			std::cin >> number_boxes;
			delete[]m_aray_boxes;
			m_aray_boxes = new Box[number_boxes];
			mem = sizeof(m_aray_boxes);
			std::cout << "\nMemory = " << mem;
			std::cout << "\nResuming...";
		}

		for (int i = 0; i < number_boxes; i++)
		FillRect(
			m_aray_boxes[i].get_loc().x,
			m_aray_boxes[i].get_loc().y,
			m_aray_boxes[i].get_width(),
			m_aray_boxes[i].get_height(),
			m_aray_boxes[i].get_col());



		return true;
	}


private:
	Box m_box1;
	int number_boxes = 3;
	Box *m_aray_boxes = new Box[number_boxes];
	long long mem;
};






int main()
{

	srand(time(NULL));

	Demo demo;
	if (demo.Construct(window_width, window_height, 1, 1))
		demo.Start();

	return 0;
}