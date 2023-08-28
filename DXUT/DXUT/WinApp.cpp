#include "WinApp.h"
#include <cmath>
#include <string>
#include "Engine.h"

void WinApp::Init()
{
	Engine::Instance()->DisableGraphics();
	xi = 10;
	yi = 10;
	xf = 100;
	yf = 100;
	hdc = GetDC(window->Id());
	vxi = 1.2;
	vyi = 0.7;
	vxf = 0.9;
	vyf = 1.5;
}

// ------------------------------------------------------------------------------

void WinApp::Update()
{
	// sai com o pressionamento da tecla ESC
	if (input->KeyPress(VK_ESCAPE))
		window->Close();

	xi += vxi;
	yi += vyi;
	xf += vxf;
	yf += vyf;

	if (window->Height() <= yf || yf <= 0) {
		vyf *= -1;
	}

	if (0 >= yi || yi >= window->Height()) {
		vyi *= -1;

	}
	if (window->Width() <= xf || xf <=0) {
		vxf *= -1;
	}
	if (0 >= xi || xi >= window->Width()) {
		vxi *= -1;
	}


	MoveToEx(hdc, xi, yi, NULL);
}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
	window->Clear();
	LineTo(hdc, xf, yf);
	Sleep(5);
}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
}


//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));
