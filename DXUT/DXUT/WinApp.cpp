#include "WinApp.h"

//#include "Engine.h"
//#include <cmath>
//#include <string>

//Engine::Instance()->DisableGraphics();
//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));


WinApp::WinApp()
{
    window->Size(640, 640);
    window->Title("Galaga");
}

void WinApp::Init()
{
    pause = new Sprite("Resources/pause_screen.png");
    pause->SetScale(0.6f);
    pause->SetPosition(window->Center());
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
}

// ------------------------------------------------------------------------------

void WinApp::OnPause() {
    pause->Draw();
}
