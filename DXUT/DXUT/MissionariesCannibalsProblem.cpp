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
    
    if (MissionariesCannibalsProblem::scene == nullptr) {
        MissionariesCannibalsProblem::scene = new Scene();
    }
}

void MissionariesCannibalsProblem::Init()
{
    imgPlayer = new Image("Resources/player.png");
    imgResult = new Image("Resources/x.png");
    //---------------
    MCAction* MoveMissionary= new MCAction(1, 0);
    MCAction* MoveCanibal = new MCAction(0, 1);
    MCAction* Move2Missionaries = new MCAction(2, 0);
    MCAction* Move2Canibals = new MCAction(0, 2);
    MCAction* MoveMissionaryAndCanibal = new MCAction(1, 1);


    actuators->push_back(MoveMissionary);
    actuators->push_back(MoveCanibal);
    actuators->push_back(Move2Missionaries);
    actuators->push_back(Move2Canibals);
    actuators->push_back(MoveMissionaryAndCanibal);

}


void MissionariesCannibalsProblem::Reset() {
    int value = this->problem;
    int countMissionaries = value;
    int countCannibals = value;
    this->SetInitial(MCS(countMissionaries, countCannibals));
    this->SetFinal(MCS(countMissionaries, countCannibals, 0, countMissionaries, countCannibals));
    this->SetCurrent(Initial());
}

// ------------------------------------------------------------------------------

void MissionariesCannibalsProblem::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();
    if (input->KeyPress(SPACE)) {
        problem++;
    }
    if (input->KeyPress(KEY_R)) {
        Reset();
        this->Search();
    }

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


void MissionariesCannibalsProblem::GenStates() {
    this->_initialState = new MCState(Current());
    this->_finalState = new MCState(_final);
}

