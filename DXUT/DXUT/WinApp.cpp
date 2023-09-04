#include "WinApp.h"

#include "Engine.h"
//#include <cmath>
//#include <string>
//#include "Engine.h"



WinApp::WinApp()
{
    window->Size(800, 600);
    window->Title("MyGame");
}

void WinApp::Init()
{
	//Engine::Instance()->DisableGraphics();
    _pause = new Sprite("Resources/pause_screen.png");
    _pause->SetScale(0.6f);
    _pause->SetPosition(window->Center());
;}

// ------------------------------------------------------------------------------

void WinApp::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();

}
// ------------------------------------------------------------------------------

void WinApp::Update()
{
    InputVerifyExit();
}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
    delete _pause;
}


//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));


void WinApp::OnPause() {
    _pause->Draw();
}
