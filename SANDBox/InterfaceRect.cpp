#include "InterfaceRect.h"
#include <assert.h>

void InterfaceRect::Prepare_Button(int xx, int yy, int w, int h, olc::Pixel col)
{
	x = xx;
	y = yy;
	width = w;
	height = h;
	color = col;
	ready = true;
}

void InterfaceRect::Draw_Button()
{
	assert(ready);

	pge->DrawRect(x, y, width, height, color);
	pge->FillRect(x + 1, y + 1, width - 1, height - 1, olc::RED);

}
