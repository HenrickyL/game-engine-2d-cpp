#include "WinApp.h"
//#include <cmath>
//#include <string>
//#include "Engine.h"

void WinApp::Init()
{
	//Engine::Instance()->DisableGraphics();
    backg = new Sprite("Resources/Background.jpg");
    shank = new Sprite("Resources/Shank.png");

    logoImg = new Image("Resources/Logo.png");
    logo1 = new Sprite(logoImg);
    logo2 = new Sprite(logoImg);

    x = 80.0f;
    y = 90.0f;

}

// ------------------------------------------------------------------------------

void WinApp::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();
}
// ------------------------------------------------------------------------------

void WinApp::InputCharacter()
{
    // desloca personagem
    if (input->KeyDown(VK_LEFT))
        x -= 50.0f * gameTime;
    if (input->KeyDown(VK_RIGHT))
        x += 50.0f * gameTime;
    if (input->KeyDown(VK_UP))
        y -= 50.0f * gameTime;
    if (input->KeyDown(VK_DOWN))
        y += 50.0f * gameTime;
}
// ------------------------------------------------------------------------------

void WinApp::Update()
{
    InputVerifyExit();
    InputCharacter();
}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
    backg->Draw(0.0f, 0.0f, Layer::BACK);
    shank->Draw(x, y);
    logo1->Draw(40.0f, 60.0f, Layer::UPPER);
    logo2->Draw(400.0f, 450.0f, Layer::LOWER);
}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
    // remove sprites da memória
    delete backg;
    delete shank;
    delete logo1;
    delete logo2;

    // remove imagem da memória
    delete logoImg;
}


//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));
