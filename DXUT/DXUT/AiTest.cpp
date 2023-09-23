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

    State* a1 = new State("Q1");
    State* a2 = new State("Q2");
    State* a3 = new State("Q3");
    State* a4 = new State("Q4");
    State* a5 = new State("Q5");
    State* a6 = new State("Q6");
    State* a7 = new State("Q7");


    // ------------------------------------------------
    a1->AddTransition(new Transition(a2, nullptr));
    a1->AddTransition(new Transition(a6, nullptr));

    a2->AddTransition(new Transition(a3, nullptr));
    a2->AddTransition(new Transition(a4, nullptr));
    
    a3->AddTransition(new Transition(a7, nullptr));
    a4->AddTransition(new Transition(a5, nullptr));
    a5->AddTransition(new Transition(a7, nullptr));
    a6->AddTransition(new Transition(a7, nullptr));
    // ------------------------------------------------
    Node* res = SearchBase::BFS(a1, a7);
    std::string s = res->GetPath();
    OutputDebugString(s.c_str());
    // ------------------------------------------------

    states.push_back(a1);
    states.push_back(a2);
    states.push_back(a3);
    states.push_back(a4);
    states.push_back(a5);
    states.push_back(a6);
    states.push_back(a7);
    
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
    tile1 = new Image("Resources/Tile1.png");
    tile2 = new Image("Resources/Tile2.png");
    tile3 = new Image("Resources/Tile3.png");
    tile4 = new Image("Resources/Tile4.png");
    tile5 = new Image("Resources/Tile5.png");
    Image* tileList[] = { tile1, tile2, tile3, tile4, tile5 };

    //----------------------------
    
}
