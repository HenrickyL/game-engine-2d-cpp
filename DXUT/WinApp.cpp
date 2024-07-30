#include "WinApp.h"

//#include "Engine.h"
//#include <cmath>
//#include <string>

//Engine::Instance()->DisableGraphics();
//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));
//OutputDebugString(s.str().c_str());


WinApp::WinApp()
{
    window->Size(640, 640);
    window->SetTitle("Galaga");
}

void WinApp::Init()
{
    imgPause = new DXImage("Resources/pause_screen.png");
    pause = new Sprite(imgPause);
    pause->SetScale(0.6f);
    pause->MoveTo(window->Center());
;}

// ------------------------------------------------------------------------------

void WinApp::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(ESCAPE))
        window->Close();

}
// ------------------------------------------------------------------------------

void WinApp::Update(double delta)
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
    if(imgPause) delete imgPause;
    if (pause)delete pause;
}

// ------------------------------------------------------------------------------

void WinApp::OnPause() {
    pause->Draw();
}
