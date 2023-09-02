#include "WinApp.h"
//#include <cmath>
//#include <string>
//#include "Engine.h"

void WinApp::Init()
{
	//Engine::Instance()->DisableGraphics();
    // inicializa objetos do jogo
    img = new Image("Resources/Logo.png");

    logo1 = new Sprite(img);
    logo2 = new Sprite(img);
    backg = new Sprite("Resources/Background.jpg");

    shank = new Shank();
}

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

    shank->Update();
}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
    backg->Draw(0.0f, 0.0f, Layer::BACK);
    logo1->Draw(40.0f, 60.0f, Layer::UPPER);
    logo2->Draw(400.0f, 450.0f, Layer::LOWER);
    shank->Draw();
}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
    // remove objetos da memória
    delete img;
    delete backg;
    delete logo1;
    delete logo2;

    delete shank;
}


//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));
