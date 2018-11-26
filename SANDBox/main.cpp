#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Box.h"
#include "Point.h"
#include "Mouse.h"
#include <ctime>

int window_width = 800;
int window_height = 600;


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
		
		// refresh screen and update mouse
		Clear(olc::BLACK);
		ms.update_loc(Point{ GetMouseX(), GetMouseY() });

		// check where click was and if any box was tagged
		if (GetMouse(0).bPressed) {

			for (int i = 0; i < number_boxes; i++)
				m_aray_boxes[i].tag_attempt(ms.location);
		}

		// update tagged boxes after mouse
		for (int i = 0; i < number_boxes; i++)
			if (m_aray_boxes[i].get_status())
				m_aray_boxes[i].follow_mouse(ms.location);

		//randomize box position, color and size
		if (GetMouse(2).bPressed)
			for (int i = 0; i < number_boxes; i++)
				m_aray_boxes[i].randomize(Point{ rand() % 750, rand() % 550 });


		// change size of box array
		if (GetKey(olc::SPACE).bPressed) {
			std::cout << "Enter value: " << std::endl;
			std::cin >> number_boxes;

			delete[]m_aray_boxes;
			m_aray_boxes = new Box[number_boxes];
			std::cout << "\nResuming...";
		}





		//Draw

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
	int number_boxes = 3;
	Box *m_aray_boxes = new Box[number_boxes];
	Mouse ms;
};






int main()
{

	srand(time(NULL));

	Demo demo;
	if (demo.Construct(window_width, window_height, 1, 1))
		demo.Start();

	return 0;
}