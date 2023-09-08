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
    alien2Img = new Image("Resources/Alien2.png");
    alien3Img = new Image("Resources/Alien3.png");
    alien4Img = new Image("Resources/Alien4.png");
    Image* list[] = { alien1Img , alien2Img, alien3Img, alien4Img };
    playerImg = new Image("Resources/Nave.png");
    missileImg = new Image("Resources/Missile.png");

    // ------------------------------
    // cria cena do jogo
    scene = new Scene();

    // ------------------------------
    // cria sprite do fundo e título
    Position center = window->Center();

    backg = new Sprite("Resources/space.png");
    backg->SetLayer(Layer::BACK);
    backg->SetPosition(center);

    title = new Sprite("Resources/Galaga.png");
    title->SetLayer(Layer::FRONT);
    center.SetY(30 + title->HalfHeight());
    title->SetPosition(center);



    //-------------------------------
    //criar player
    Player* player = new Player(playerImg, missileImg);
    player->MoveTo(Position(window->Center().X(), window->Height() - 50.f));
    scene->Add(player, MOVING);

    //-------------------------------
    //criar alien
    float offset = 80;
    float posY = 260;

    Alien* alien;
    bool invert = false;
    float speed = 80.0f;

    for(int row=0; row< 4; row++)
    {
        for (int col = 0; col < 4; col++) {
            Image* img = list[col];
            alien = new Alien(img);
            float posX = col * offset;
            if (row % 2 == 1) {
                posX += offset / 2.0f; 
            }
           
            if (col % 2 == 0) {
                speed = 80.0f;
                alien->SetSpeed(Vector::Right * speed);
                alien->MoveTo(Position(posX, posY));
            }
            else {
                speed = 80.0f;
                alien->SetSpeed(Vector::Left * speed);
                alien->MoveTo(Position(window->Width()- posX, posY));

            }
            scene->Add(alien, STATIC);
        }
        posY += 80;
    }
   

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

    // detecção e resolução de colisão
    scene->CollisionDetection();
}


// ------------------------------------------------------------------------------

void Galaga::Draw()
{
    if (viewScene) {
        // desenha pano de fundo
        backg->Draw();

        // desenha título do jogo
        title->Draw();

        // desenha cena
        scene->Draw();
    }

    if (viewBBox) {
        scene->DrawBBox();
    }
    
}

// ------------------------------------------------------------------------------

void Galaga::Finalize()
{
    delete pause;
    //delete imgs
    delete alien1Img;
    delete alien2Img;
    delete alien3Img;
    delete alien4Img;
    delete playerImg;
    delete missileImg;
    // apaga sprites
    delete backg;
    delete title;
    // apaga cena do jogo
    delete scene;
}


void Galaga::OnPause() {
    pause->Draw();
}
