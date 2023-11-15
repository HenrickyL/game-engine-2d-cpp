#include "ShortPathProblem.h"
// ------------------------------------------------------------------------------
#include "Player.h"
// ------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Scene* ShortPathProblem::scene = nullptr;

// ------------------------------------------------------------------------------

ShortPathProblem::ShortPathProblem()
{
    window->Size(800, 500);
    window->Title("ShortPathProblem");
}

void ShortPathProblem::Init()
{
    Reset();


    imgPlayer = new Image("Resources/player.png");
    imgResult = new Image("Resources/x.png");

    ///TODO: Delete Player
    Position initial(100, 100);
    Player* player = new Player(imgPlayer, initial);
    Position target (window->Center()); // (640, 480)
    player->SetTarget(target);

    scene->Add(player, MOVING);
    //---------------
    targetLocal = new Sprite(imgResult);
    targetLocal->SetScale(0.01f);
    targetLocal->SetPosition(target);
}

// ------------------------------------------------------------------------------

void ShortPathProblem::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();

}
// ------------------------------------------------------------------------------

void ShortPathProblem::Update()
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

void ShortPathProblem::Draw()
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

void ShortPathProblem::Finalize()
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

    for (auto* s : states) {
        delete s;
    }
}


void ShortPathProblem::OnPause() {
    pause->Draw();
}

void ShortPathProblem::Reset() {
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
