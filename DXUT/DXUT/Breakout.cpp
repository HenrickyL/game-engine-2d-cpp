#include "Breakout.h"
// ------------------------------------------------------------------------------
#include "Player.h"
#include "Ball.h"
#include "Block.h"

// ------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Scene* Breakout::scene = nullptr;

// ------------------------------------------------------------------------------

Breakout::Breakout()
{
    window->Size(960, 540);
    window->Title("Breakout");
}

void Breakout::Init()
{
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

    // ---------------------------
    // cria jogador
    playerImg = new Image("Resources/Player.png");
    Player* player = new Player(playerImg);
    player->MoveTo(Position(window->Center().X(), window->Height() - 30.0f));
    scene->Add(player, MOVING);

    // ---------------------------
    // cria bola
    ballImg = new Image("Resources/Ball.png");
    Ball* ball = new Ball(player, ballImg);
    scene->Add(ball, MOVING);
    //----------------------------
    // criar os blocks
    int numBlocksX = 8;
    int numBlocksY = 5;

    int windowWidth = window->Width();
    int windowHeight = window->Height();

    int horizontalSpacing = 30; // Ajuste conforme necessário
    int verticalSpacing = 25;   // Ajuste conforme necessário

    Block* b = new Block(tile1);
    int blockWidth = b->Width();
    int blockHeight = b->Height();
    delete b;

    int offsetX = (windowWidth - (numBlocksX * blockWidth + (numBlocksX - 1) * horizontalSpacing)) / 2;
    int offsetY = (windowHeight - (numBlocksY * blockHeight + (numBlocksY - 1) * verticalSpacing)) / 2;
    for (int lin = 0; lin < numBlocksY; lin++) {
        for (int row = 0; row < numBlocksX; row++) {
            Block* block = new Block(tileList[lin]);
            int x = offsetX + row * (blockWidth + horizontalSpacing);
            int y = offsetY + lin * (blockHeight + verticalSpacing);
            block->MoveTo(Position(x, y));
            scene->Add(block, STATIC);
        }
    }
    
}

// ------------------------------------------------------------------------------

void Breakout::InputVerifyExit()
{
    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();

}
// ------------------------------------------------------------------------------

void Breakout::Update()
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

void Breakout::Draw()
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

void Breakout::Finalize()
{
    delete pause;
    //delete imgs
    delete tile1;
    delete tile2;
    delete tile3;
    delete tile4;
    delete playerImg;
    delete ballImg;
    // apaga sprites
    delete backg;
    // apaga cena do jogo
    delete scene;
}


void Breakout::OnPause() {
    pause->Draw();
}