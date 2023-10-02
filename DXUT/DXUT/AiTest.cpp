#include "AiTest.h"
// ------------------------------------------------------------------------------
#include "StatePosition.h"
#include "MovimentAction.h"
#include "Player.h"

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


    imgPlayer = new Image("Resources/player.png");
    imgResult = new Image("Resources/x.png");


    Position initial(800, 500);
    Player* player = new Player(imgPlayer, initial);
    Position target (800, 500);
    player->SetTarget(target);

    scene->Add(player, MOVING);
    //---------------
    targetLocal = new Sprite(imgResult);
    targetLocal->SetScale(0.01f);
    targetLocal->SetPosition(target);
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

    if (targetLocal) {
        targetLocal->Draw();
    }
}

// ------------------------------------------------------------------------------

void AiTest::Finalize()
{
    if(pause)delete pause;
    //delete imgs
    if (imgPlayer)delete imgPlayer;
    if (imgResult)delete imgResult;
    // apaga sprites
    if (backg)delete backg;
    // apaga cena do jogo
    if (scene)delete scene;
    if (targetLocal) delete targetLocal;

    for (State* s : states) {
        delete s;
    }
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

    //----------------------------
    
}
