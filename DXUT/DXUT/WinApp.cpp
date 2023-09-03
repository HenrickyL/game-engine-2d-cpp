#include "WinApp.h"

#include "Engine.h"
//#include <cmath>
//#include <string>
//#include "Engine.h"


WinApp::WinApp()
{
    window->Size(800, 600);
    window->Title("Frogger");
}

void WinApp::Init()
{
	//Engine::Instance()->DisableGraphics();
    // inicializa objetos do jogo
     // carrega imagens do jogo
    woodSmall   = new Image("Resources/woodSmall.png");
    woodBig     = new Image("Resources/woodBig.png");
    turtleSmall = new Image("Resources/turtlesSmall.png");
    turtleBig   = new Image("Resources/turtlesBig.png");
    truck       = new Image("Resources/truck.png");
    car1        = new Image("Resources/car1.png");
    car2        = new Image("Resources/car2.png");
    car3        = new Image("Resources/car3.png");
    car4        = new Image("Resources/car4.png");

    //_sprite Win Lose
    win = new Sprite("Resources/you_win.png");
    //win->SetScale(0.5);

    lose = new Sprite("Resources/game_over.png");
    lose->SetScale(0.25);

    Pause = new Sprite("Resources/pause_screen.png");
    Pause->SetScale(0.6);


    // inicializa sprites do jogo
    background = new Sprite("Resources/Track.jpg");

    frogger = new Frogger();

    // ---------------------------
    // obstáculos da água

    obj = new Obstacle(woodSmall, 80);
    obj->SetInitialPosition(150, 109);
    objects.push_back(obj);

    obj = new Obstacle(woodSmall, 80);
    obj->SetInitialPosition(550, 109);
    objects.push_back(obj);

    obj = new Obstacle(turtleSmall, 70);
    obj->SetInitialPosition(480, 142);
    objects.push_back(obj);

    obj = new Obstacle(turtleSmall, 70);
    obj->SetInitialPosition(680, 142);
    objects.push_back(obj);

    obj = new Obstacle(woodBig, 50);
    obj->SetInitialPosition(200, 190);
    objects.push_back(obj);

    obj = new Obstacle(woodBig, 50);
    obj->SetInitialPosition(700, 190);
    objects.push_back(obj);

    obj = new Obstacle(woodSmall, 60);
    obj->SetInitialPosition(350, 229);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->SetInitialPosition(150, 262);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->SetInitialPosition(450, 262);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->SetInitialPosition(750, 262);
    objects.push_back(obj);

    // ---------------------------
    // obstáculos da pista

    obj = new Obstacle(truck, 50);
    obj->SetInitialPosition(300, 344);
    objects.push_back(obj);

    obj = new Obstacle(truck, 50);
    obj->SetInitialPosition(700, 344);
    objects.push_back(obj);

    obj = new Obstacle(car1, 90);
    obj->SetInitialPosition(350, 384);
    objects.push_back(obj);

    obj = new Obstacle(car4, 90);
    obj->SetInitialPosition(600, 387);
    objects.push_back(obj);

    obj = new Obstacle(car2, 110);
    obj->SetInitialPosition(500, 427);
    objects.push_back(obj);

    obj = new Obstacle(car3, 100);
    obj->SetInitialPosition(750, 467);
    objects.push_back(obj);

    obj = new Obstacle(car4, 80);
    obj->SetInitialPosition(450, 507);
    objects.push_back(obj);

}

// ------------------------------------------------------------------------------

bool WinApp::IsCollide(Frogger* frog, Obstacle* obst)
{
    // Coordenadas do Frog com âncora no centro
    float frogCenterX = frog->X();  // Posição X do centro do Frog
    float frogCenterY = frog->Y();  // Posição Y do centro do Frog
    float frogHalfWidth = frog->Width() / 2;
    float frogHalfHeight = frog->Height() / 2;

    // Coordenadas do Obstacle com âncora no canto superior esquerdo
    float obstLeft = obst->X() + obst->Width()/2;
    float obstRight = obst->X() + obst->Width();
    float obstTop = obst->Y();
    float obstBottom = obst->Y() + obst->Height()/2;

    // Verifique a colisão entre os objetos com base nas coordenadas ajustadas
    return (frogCenterX + frogHalfWidth > obstLeft &&  // Colisão direita
        frogCenterX - frogHalfWidth < obstRight &&  // Colisão esquerda
        frogCenterY - frogHalfHeight < obstBottom && // Colisão superior
        frogCenterY + frogHalfHeight > obstTop);     // Colisão inferior
}



void WinApp::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();
}
// ------------------------------------------------------------------------------

void WinApp::Update()
{
    if(gameEnd)
    {
        if (input->KeyPress(SPACE))
        {
            gameEnd = false;
            gameWin = false;
            frogger->Reset();
            for (auto obj : objects)
                obj->Reset();
        }
    }else
    {
        InputVerifyExit();

        // atualiza posição do sapo
        frogger->Update();
        

        if (frogger->Y() < 60 + 6 * frogger->Jump() && frogger->Y() > 60 + frogger->Jump()) {
            frogger->InWatter();
        }
        else {
            frogger->InFloor();
        }

       

        for (auto obj : objects)
            if (IsCollide(frogger, obj))
            {
                gameEnd = true;
                gameWin = false;
                frogger->IsDie();
                frogger->Draw();
            }

        if (frogger->Y() < 60 + frogger->Jump())
        {
            gameEnd = true;
            gameWin = true;
        }
    }
    // move objetos
    for (auto obj : objects)
        obj->Update();
    
    
}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
    // desenha pano de fundo
    background->Draw(0.0f, 0.0f, Layer::BACK);

    // desenha sapo
    frogger->Draw();

    // desenha obstáculos
    for (auto obj : objects)
        obj->Draw();

    if (gameEnd)
    {
        if (gameWin)
        {
            win->Draw(window->CenterX() - win->Width() / 2, window->CenterY() - win->Height() / 2, Layer::FRONT);
        }else
        {
            lose->Draw(window->CenterX() - lose->Width() / 2, window->CenterY() - lose->Height() / 2, Layer::FRONT);
        }
    }

}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
    // remove objetos da memória
    delete background;
    delete frogger;
    delete win;
    delete lose;
    delete Pause;

    // remove obstáculos
    for (auto obj : objects)
        delete obj;

    // descarrega imagens da memória
    delete woodSmall;
    delete woodBig;
    delete turtleSmall;
    delete turtleBig;
    delete truck;
    delete car1;
    delete car2;
    delete car3;
    delete car4;
}


//SetPixel(GetDC(window->Id()), 20, 20, RGB(255, 0, 0));


void WinApp::OnPause() {
    Pause->Draw(window->CenterX() - Pause->Width() / 2, window->CenterY() - Pause->Height() / 2, Layer::FRONT);
}
