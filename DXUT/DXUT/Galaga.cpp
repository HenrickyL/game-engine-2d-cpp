#include "Galaga.h"

// ------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Scene* Galaga::scene = nullptr;

// ------------------------------------------------------------------------------

Galaga::Galaga()
{
    window->Size(640, 640);
    window->Title("Galaga");
}

void Galaga::Init()
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

    ;
}

// ------------------------------------------------------------------------------

void Galaga::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();

}
// ------------------------------------------------------------------------------

void Galaga::Update()
{
    InputVerifyExit();

    // atualiza objetos da cena
    scene->Update();
}


// ------------------------------------------------------------------------------

void Galaga::Draw()
{
    // desenha pano de fundo
    backg->Draw();

    // desenha título do jogo
    title->Draw();

    // desenha cena
    scene->Draw();
}

// ------------------------------------------------------------------------------

void Galaga::Finalize()
{
    delete pause;
    // apaga sprites
    delete backg;
    delete title;
    // apaga cena do jogo
    delete scene;
}


void Galaga::OnPause() {
    pause->Draw();
}
