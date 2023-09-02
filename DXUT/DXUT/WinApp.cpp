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
    woodSmall = new Image("Resources/woodSmall.png");
    woodBig = new Image("Resources/woodBig.png");
    turtleSmall = new Image("Resources/turtlesSmall.png");
    turtleBig = new Image("Resources/turtlesBig.png");
    truck = new Image("Resources/truck.png");
    car1 = new Image("Resources/car1.png");
    car2 = new Image("Resources/car2.png");
    car3 = new Image("Resources/car3.png");
    car4 = new Image("Resources/car4.png");

    // inicializa sprites do jogo
    background = new Sprite("Resources/Track.jpg");

    frogger = new Frogger();

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
}


// ------------------------------------------------------------------------------

void WinApp::Draw()
{
    // desenha pano de fundo
    background->Draw(0.0f, 0.0f, Layer::BACK);

    // desenha sapo
    frogger->Draw();
}

// ------------------------------------------------------------------------------

void WinApp::Finalize()
{
    // remove objetos da memória
    delete background;
    delete frogger;

    //// remove obstáculos
    //for (auto obj : objects)
    //    delete obj;

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
