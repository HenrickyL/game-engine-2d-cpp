#include "MissionariesCannibalsProblem.h"
// ------------------------------------------------------------------------------
Scene* MissionariesCannibalsProblem::scene = nullptr;
// ------------------------------------------------------------------------------

#include "MCAction.h"
#include "MCState.h"
#include "MCObj.h"
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
    imgMissionary = new Image("Resources/missionary.png");
    imgCannibal = new Image("Resources/cannibal.png");
    imgBoat = new Image("Resources/boat.png");

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
    this->ClearMemory();
    
    int countMissionaries = numMissionaries;
    int countCannibals = numCannibals;
    this->SetInitial(MCS(countMissionaries, countCannibals));
    this->SetFinal(MCS(countMissionaries, countCannibals, 0, countMissionaries, countCannibals));
    this->SetCurrent(Initial());

    UpdatePositionObj();
}


void MissionariesCannibalsProblem::UpdatePositionObj() {
    scene->Clear();
    float P12X = window->Center().X() / 3;
    float POrigin = window->Center().Y();
    float PTarget = window->Center().X() * 1.2;
    float offSetX = 25.0f;


    MCObj* obj;
    for (int i = 0; i < _current.MissionariesOrigin(); i++) {
        obj = new MCObj(imgMissionary);
        Position p = Position(P12X, POrigin);
        p.Translate(Vector(i * offSetX, -POrigin / 3));
        obj->MoveTo(p);
        scene->Add(obj, STATIC);
    }
    for (int i = 0; i < _current.CannibalsOrigin(); i++) {
        obj = new MCObj(imgCannibal);
        Position p = Position(P12X, POrigin);;
        p.Translate(Vector(i * offSetX, POrigin / 2));
        obj->MoveTo(p);
        scene->Add(obj, STATIC);
    }

    for (int i = 0; i < _current.MissionariesTarget(); i++) {
        obj = new MCObj(imgMissionary);
        Position p = Position(P12X, POrigin);
        p.Translate(Vector(i * offSetX + PTarget, -POrigin / 3));
        obj->MoveTo(p);
        scene->Add(obj, STATIC);
    }
    for (int i = 0; i < _current.CannibalsTarget(); i++) {
        obj = new MCObj(imgCannibal);
        Position p = Position(P12X, POrigin);;
        p.Translate(Vector(i * offSetX + PTarget, POrigin / 2));
        obj->MoveTo(p);
        scene->Add(obj, STATIC);
    }
    obj = new MCObj(imgBoat, 0.05f);
    Position p = window->Center();
    p.Translate(Vector(_current.Boat() == 0 ? P12X : -P12X, 0));
    obj->MoveTo(p);
    scene->Add(obj, STATIC);

}


// ------------------------------------------------------------------------------

void MissionariesCannibalsProblem::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();
    if (input->KeyPress(KEY_M)) {
        numMissionaries++;
    }
    if (input->KeyPress(KEY_C)) {
        numCannibals++;
    }

    if (input->KeyPress(SPACE)) {
        if (pivot != nullptr) {
            MCState* state = dynamic_cast<MCState*>(pivot->GetState());
            _current = state->Value();
            int n = pivot->GetPathLength();
            pivot = pivot->Father();
            window->Clear();
            UpdatePositionObj();
        }
        else {
            pivot = path;
        }
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
    if (imgMissionary)delete imgMissionary;
    if (imgCannibal)delete imgCannibal;
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

