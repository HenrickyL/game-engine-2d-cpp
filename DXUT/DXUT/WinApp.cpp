#include "WinApp.h"
#include <cmath>
#include <string>
#include "Engine.h"

void WinApp::Init()
{
	//Engine::Instance()->DisableGraphics();
}

// ------------------------------------------------------------------------------

void WinApp::Update()
{
	// sai com o pressionamento da tecla ESC
	if (input->KeyPress(VK_ESCAPE))
		window->Close();



}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
}


//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));
