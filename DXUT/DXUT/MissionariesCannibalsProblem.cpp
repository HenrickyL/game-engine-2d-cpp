#include "MissionariesCannibalsProblem.h"
// ------------------------------------------------------------------------------
Scene* MissionariesCannibalsProblem::scene = nullptr;
// ------------------------------------------------------------------------------

#include "MCAction.h"
#include "MCState.h"

MissionariesCannibalsProblem::MissionariesCannibalsProblem()
{
    window->Size(800, 500); 
    window->Title("MissionariesCannibalsProblem");
    this->InstanceAgent();

    this->SetInitial(MCS(3, 3));
    this->SetFinal(MCS(0, 0, 0));
    this->SetCurrent(Initial());
}

void MissionariesCannibalsProblem::Init()
{
    Reset();

    imgPlayer = new Image("Resources/player.png");
    imgResult = new Image("Resources/x.png");
    //---------------
    MCAction* MoveMissionary= new MCAction(1, 0);
    MCAction* MoveCanibal = new MCAction(0, 1);
    MCAction* Move2Missionaries = new MCAction(2, 0);
    MCAction* Move2Canibals = new MCAction(0, 2);

    Actuators()->push_back(MoveMissionary);
    Actuators()->push_back(MoveCanibal);
    Actuators()->push_back(Move2Missionaries);
    Actuators()->push_back(Move2Canibals);
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
    this->DeleteInstanceAgent();
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



void MissionariesCannibalsProblem::GenStates() {
    this->_initialState = new MCState(Current());
    this->_finalState = new MCState(_final);
}
