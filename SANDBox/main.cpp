#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Box.h"
#include "Point.h"
#include "Mouse.h"
#include "BoxesHandler.h"
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
		
		SetPixelMode(olc::Pixel::ALPHA);

		// refresh screen and update mouse
		Clear(olc::BLACK);
		ms.update_loc(Point{ GetMouseX(), GetMouseY() });

		// check where click was and if any box was tagged - also, check if mouse is carrying anything, if so, drop all, else check for boxes
		if (GetMouse(0).bPressed) {
			if (ms.carrying) {
				box_hand.dropBox();
				ms.carrying = false;
			}

			else 
				box_hand.checkForBox(ms.location);			
		}



		// update tagged boxes after mouse location -- also controls swap width/height 
		if (box_hand.hasBox()) {
			box_hand.CarriedBox().follow_mouse(ms.location);
			ms.carrying = true;

			if (GetMouse(1).bPressed)
				box_hand.CarriedBox().flip();


			if (GetKey(olc::Q).bHeld)
				box_hand.CarriedBox().fadeOut();
			if (GetKey(olc::W).bHeld)
				box_hand.CarriedBox().fadeIn();
		}
	

		//randomize box position, color and size
		if (GetMouse(2).bPressed)
			box_hand.throwBoxes();


		// change size of box array
		if (GetKey(olc::SPACE).bPressed)
			box_hand.changeBoxQuantity();
		


		box_hand.drawBoxes();


		return true;
	}


private:
	Mouse ms;
	BoxesHandler box_hand{ this };

};






int main()
{

	srand(time(NULL));

	Demo demo;
	if (demo.Construct(window_width, window_height, 1, 1))
		demo.Start();

	return 0;
}