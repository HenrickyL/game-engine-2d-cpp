#include "WinApp.h"

#include "Engine.h"
//#include <cmath>
//#include <string>

//Engine::Instance()->DisableGraphics();


// ------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Scene* WinApp::scene = nullptr;

// ------------------------------------------------------------------------------

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

    // ------------------------------
    // cria cena do jogo
    scene = new Scene();

    // ------------------------------
    // cria sprite do fundo e título
    Point center = window->Center();

    backg = new Sprite("Resources/space.png");
    backg->SetLayer(Layer::BACK);
    backg->SetPosition(center);

    title = new Sprite("Resources/Galaga.png");
    title->SetLayer(Layer::FRONT);
    center.SetY(30 + title->HalfHeight());
    title->SetPosition(center);

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

    // atualiza objetos da cena
    scene->Update();
}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
    // desenha pano de fundo
    backg->Draw();

    // desenha título do jogo
    title->Draw();

    // desenha cena
    scene->Draw();
}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
    delete pause;
    // apaga sprites
    delete backg;
    delete title;
    // apaga cena do jogo
    delete scene;
}


//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));


void WinApp::OnPause() {
    pause->Draw();
}
