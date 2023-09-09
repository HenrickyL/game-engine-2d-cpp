#include "Breakout.h"
// ------------------------------------------------------------------------------
#include "Player.h"

// ------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Scene* Breakout::scene = nullptr;

// ------------------------------------------------------------------------------

Breakout::Breakout()
{
    window->Size(960, 540);
    window->Title("Breakout");
}

void Breakout::Init()
{
    pause = new Sprite("Resources/pause_screen.png");
    pause->SetScale(0.6f);
    pause->SetPosition(window->Center());

    backg = new Sprite("Resources/Background.jpg");
    backg->SetPosition(window->Center());

    // --------------------------
    scene = new Scene();
    // --------------------------


}

// ------------------------------------------------------------------------------

void Breakout::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();

}
// ------------------------------------------------------------------------------

void Breakout::Update()
{
    InputVerifyExit();
    //BoundingBox
    if (input->KeyPress(KEY_B)) {
        viewBBox = !viewBBox;
    }
    //Scene
    if (input->KeyPress(KEY_S)) {
        viewScene = !viewScene;
    }

    // atualiza objetos da cena
    scene->Update();

    // detec��o e resolu��o de colis�o
    scene->CollisionDetection();
}


// ------------------------------------------------------------------------------

void Breakout::Draw()
{
    if (viewScene) {
        // desenha pano de fundo
        backg->Draw();

        // desenha cena
        scene->Draw();
    }

    if (viewBBox) {
        scene->DrawBBox();
    }

}

// ------------------------------------------------------------------------------

void Breakout::Finalize()
{
    delete pause;
    //delete imgs
   
    // apaga sprites
    delete backg;
    // apaga cena do jogo
    delete scene;
}


void Breakout::OnPause() {
    pause->Draw();
}