#include "WinApp.h"
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

    // inicializa sprites do jogo
    background = new Sprite("Resources/Track.jpg");

    frogger = new Frogger();

    // ---------------------------
    // obstáculos da água

    obj = new Obstacle(woodSmall, 80);
    obj->MoveTo(150, 109);
    objects.push_back(obj);

    obj = new Obstacle(woodSmall, 80);
    obj->MoveTo(550, 109);
    objects.push_back(obj);

    obj = new Obstacle(turtleSmall, 70);
    obj->MoveTo(480, 142);
    objects.push_back(obj);

    obj = new Obstacle(turtleSmall, 70);
    obj->MoveTo(680, 142);
    objects.push_back(obj);

    obj = new Obstacle(woodBig, 50);
    obj->MoveTo(200, 190);
    objects.push_back(obj);

    obj = new Obstacle(woodBig, 50);
    obj->MoveTo(700, 190);
    objects.push_back(obj);

    obj = new Obstacle(woodSmall, 60);
    obj->MoveTo(350, 229);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->MoveTo(150, 262);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->MoveTo(450, 262);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->MoveTo(750, 262);
    objects.push_back(obj);

    // ---------------------------
    // obstáculos da pista

    obj = new Obstacle(truck, 50);
    obj->MoveTo(300, 344);
    objects.push_back(obj);

    obj = new Obstacle(truck, 50);
    obj->MoveTo(700, 344);
    objects.push_back(obj);

    obj = new Obstacle(car1, 90);
    obj->MoveTo(350, 384);
    objects.push_back(obj);

    obj = new Obstacle(car4, 90);
    obj->MoveTo(600, 387);
    objects.push_back(obj);

    obj = new Obstacle(car2, 110);
    obj->MoveTo(500, 427);
    objects.push_back(obj);

    obj = new Obstacle(car3, 100);
    obj->MoveTo(750, 467);
    objects.push_back(obj);

    obj = new Obstacle(car4, 80);
    obj->MoveTo(450, 507);
    objects.push_back(obj);

}

// ------------------------------------------------------------------------------

void WinApp::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();
}
// ------------------------------------------------------------------------------

void WinApp::Update()
{
    InputVerifyExit();

    // atualiza posição do sapo
    frogger->Update();


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

}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
    // remove objetos da memória
    delete background;
    delete frogger;

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
