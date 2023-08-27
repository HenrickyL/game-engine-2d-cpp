#include "WinApp.h"
#include <cmath>
void WinApp::Init()
{
	
}

// ------------------------------------------------------------------------------

void WinApp::Update()
{
	// sai com o pressionamento da tecla ESC
	if (input->KeyPress(VK_ESCAPE))
		window->Close();

	
	if (input->KeyDown(VK_LBUTTON) || input->KeyDown(VK_RBUTTON)) {
		lastX = input->MouseX();
		lastY = input->MouseY();
		if (input->KeyDown(VK_RBUTTON)) {
			color = RGB(0, 255, 255);
			isRight = true;
		}
		else if(input->KeyDown(VK_LBUTTON)){
			color = RGB(255, 0, 0);
			isRight = false;
		}
		if (!input->KeyPress(VK_SHIFT)) {
			isActivate = true;
		}
		else {
			isActivate = false;
		}

		/*if (isActivate) {
			if (R > 50) {
				increase = 1 - tax;
			}
			else if(R < 1){
				increase = 1 + tax;
			}
		}
		else {
			if (R < RDefaut - 0.1) {
				increase = 1 + tax;
			}
			else if (R  > RDefaut + 0.1) {
				increase = 1 - tax;
			}
			else {
				increase = 1;
			}
		}*/
		if (isActivate) {
			R *= increase;
		}
		else {
			R /= increase;
		}
	}
	
	

	if (input->KeyDown(TAB)) {
		window->Clear();
	}
}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
	if (input->KeyDown(VK_LBUTTON)) {
		HDC hdc = GetDC(window->Id());
		int angle = 0;
		SetPixel(GetDC(window->Id()), lastX, lastY, RGB(0, 255, 0));
		for (int angle = 0; angle < 1000;  angle++) {
			double radians = angle * 3.1415 / 180.0;
			float d = 0.2;
			d *= isRight ? 1 : -1;
			int xDT = int(R * cos(radians)) ;
			int yDT = int(R * sin(radians)) ;
			
			int x = lastX + xDT;
			int y = lastY + yDT;
			SetPixel(hdc, x, y, color);
		}
	}
	
}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
}


//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));
