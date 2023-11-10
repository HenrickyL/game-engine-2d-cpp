#include "MissionariesCannibalsProblem.h"
// ------------------------------------------------------------------------------
#include "Player.h"
// ------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Scene* MissionariesCannibalsProblem::scene = nullptr;

// ------------------------------------------------------------------------------

MissionariesCannibalsProblem::MissionariesCannibalsProblem()
{
    window->Size(800, 500);
    window->Title("MissionariesCannibalsProblem");
}

void MissionariesCannibalsProblem::Init()
{
    Reset();


    imgPlayer = new Image("Resources/player.png");
    imgResult = new Image("Resources/x.png");


    Position initial(100, 100);
    Player* player = new Player(imgPlayer, initial);
    Position target(window->Center()); // (640, 480)
    player->SetTarget(target);

    scene->Add(player, MOVING);
    //---------------
    targetLocal = new Sprite(imgResult);
    targetLocal->SetScale(0.01f);
    targetLocal->SetPosition(target);
}

// ------------------------------------------------------------------------------

void MissionariesCannibalsProblem::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();

}
// ------------------------------------------------------------------------------

void MissionariesCannibalsProblem::Update()
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

void MissionariesCannibalsProblem::Draw()
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

void MissionariesCannibalsProblem::Finalize()
{
    if (pause)delete pause;
    //delete imgs
    if (imgPlayer)delete imgPlayer;
    if (imgResult)delete imgResult;
    // apaga sprites
    if (backg)delete backg;
    // apaga cena do jogo
    if (scene)delete scene;
    if (targetLocal) delete targetLocal;

    for (auto* s : states) {
        delete s;
    }
}


void MissionariesCannibalsProblem::OnPause() {
    pause->Draw();
}

void MissionariesCannibalsProblem::Reset() {
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
