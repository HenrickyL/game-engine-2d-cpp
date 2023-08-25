#include "WinApp.h"

void WinApp::Init()
{
	
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