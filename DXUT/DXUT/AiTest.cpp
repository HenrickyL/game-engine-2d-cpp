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


    Player* player = new Player(imgPlayer);
    player->MoveTo(Position(10, 10));
    Player* FinalPos = new Player(imgResult);
    FinalPos->MoveTo(Position(800, 500));




    StatePosition* A = new StatePosition(player->GetPosition());
    StatePosition* B = new StatePosition(FinalPos->GetPosition());


    Action* up = new MovimentAction(Vector::Up);
    Action* down = new MovimentAction(Vector::Down);
    Action* left = new MovimentAction(Vector::Left);
    Action* right = new MovimentAction(Vector::Right);

    vector<Action*> actions;
    actions.push_back(up);
    actions.push_back(down);
    actions.push_back(left);
    actions.push_back(right);

    std::string s = "";
    OutputDebugString("------------");

    Node* result = SearchMethods::HeuristicSearch(A, B, actions);
    int value = result->GetPathLength();
    s = "\nHeuristic: {\n\t" + result->GetPath() + "\n}\n\tCost: " + std::to_string(result->Cost());
    OutputDebugString(s.c_str());


    delete up, down, left, right;
    delete A, B;
    delete result;
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
    if (imgPlayer)delete imgPlayer;
    if (imgResult)delete imgResult;
    // apaga sprites
    if (!backg)delete backg;
    // apaga cena do jogo
    if (!scene)delete scene;

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
