#include "Galaga.h"
// ------------------------------------------------------------------------------
#include "Alien.h"
#include "Player.h"

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
    //-------------------------------
    //Aloca imagens
    alien1Img = new Image("Resources/Alien1.png");
    playerImg = new Image("Resources/Nave.png");


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



    //-------------------------------
    //criar player
    Player* player = new Player(playerImg);
    player->MoveTo(Point(window->Center().X(), window->Height() - 50.f));
    scene->Add(player);

    //-------------------------------
    //criar alien
    float offset = 80;
    float posY = 260;

    Alien* alien;
    alien = new Alien(alien1Img);
    alien->MoveTo(Point(200, posY));
    scene->Add(alien);

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
    //delete imgs
    delete alien1Img;
    // apaga sprites
    delete backg;
    delete title;
    // apaga cena do jogo
    delete scene;
}


void Galaga::OnPause() {
    pause->Draw();
}
