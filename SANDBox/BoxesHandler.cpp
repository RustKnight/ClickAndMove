#include "BoxesHandler.h"



void BoxesHandler::checkForBox(Point loc)
{

	// check for the top most box, if found store and stop
	for (int i = number_boxes - 1; i >= 0; i--)
		if (m_aray_boxes[i].tag_attempt(loc)) {
			selected_box = &m_aray_boxes[i];
			carrying = true;
			break;
		}

}

void BoxesHandler::dropBox()
{
	selected_box->deselect();
	carrying = false;
}

Box& BoxesHandler::CarriedBox()
{

	return *selected_box;
}

void BoxesHandler::throwBoxes()
{
	for (int i = 0; i < number_boxes; i++)
		m_aray_boxes[i].randomize(Point{ rand() % 750, rand() % 550 });
}

void BoxesHandler::adjustBoxes()
{
	std::cout << "Enter value: " << std::endl;
	std::cin >> number_boxes;

	delete[]m_aray_boxes;
	m_aray_boxes = new Box[number_boxes];
	std::cout << "\nResuming...";

}

void BoxesHandler::drawBoxes()
{

	for(int i = 0; i < number_boxes; i++)
		pcg->FillRect(
			m_aray_boxes[i].get_loc().x,
			m_aray_boxes[i].get_loc().y,
			m_aray_boxes[i].get_width(),
			m_aray_boxes[i].get_height(),
			m_aray_boxes[i].get_col());

}
