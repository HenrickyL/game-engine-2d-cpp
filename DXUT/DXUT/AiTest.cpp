#include "AiTest.h"
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Scene* AiTest::scene = nullptr;

// ------------------------------------------------------------------------------

AiTest::AiTest()
{
    window->Size(960, 540);
    window->Title("AiTest");
}

void AiTest::Init()
{
    Reset();
    
}

// ------------------------------------------------------------------------------

void AiTest::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();

}
// ------------------------------------------------------------------------------

void AiTest::Update()
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

void AiTest::Draw()
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

void AiTest::Finalize()
{
    if(!pause)delete pause;
    //delete imgs
    if (!tile1)delete tile1;
    if (!tile2)delete tile2;
    if (!tile3)delete tile3;
    if (!tile4)delete tile4;
    // apaga sprites
    if (!backg)delete backg;
    // apaga cena do jogo
    if (!scene)delete scene;
}


void AiTest::OnPause() {
    pause->Draw();
}

void AiTest::Reset() {
    Finalize();

    pause = new Sprite("Resources/pause_screen.png");
    pause->SetScale(0.6f);
    pause->SetPosition(window->Center());

    backg = new Sprite("Resources/Background.jpg");
    backg->SetPosition(window->Center());
    backg->SetLayer(Layer::BACK);

    // --------------------------
    scene = new Scene();
    // --------------------------

    // carregar imagens
    tile1 = new Image("Resources/Tile1.png");
    tile2 = new Image("Resources/Tile2.png");
    tile3 = new Image("Resources/Tile3.png");
    tile4 = new Image("Resources/Tile4.png");
    tile5 = new Image("Resources/Tile5.png");
    Image* tileList[] = { tile1, tile2, tile3, tile4, tile5 };

    //----------------------------
    
}
