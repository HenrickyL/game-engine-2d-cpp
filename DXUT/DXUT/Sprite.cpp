#include "Sprite.h"
#include "Engine.h"
// -------------------------------------------------------------------------------
// Inicialização de membros estáticos das classes

// valores de profundidade predefinidos
const float Layer::FRONT = 0.00f;
const float Layer::UPPER = 0.25f;
const float Layer::MIDDLE = 0.50f;
const float Layer::LOWER = 0.75f;
const float Layer::BACK = 0.99f;

// ---------------------------------------------------------------------------------

Sprite::Sprite(string filename)
{
    // carrega imagem
    image = new Image(filename);
    localImage = true;

    // configura registro sprite
    ResetSprite();
}

// ---------------------------------------------------------------------------------

Sprite::Sprite(const Image* img)
{
    // aponta para imagem externa
    image = img;
    localImage = false;

    // configura registro sprite
    ResetSprite();

}

// ---------------------------------------------------------------------------------

Sprite::~Sprite()
{
    if (localImage)
        delete image;
}

// ---------------------------------------------------------------------------------


void Sprite::ResetSprite()
{
    sprite.texture = image->View();
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.x = 0;
    sprite.y = 0;
    sprite.scale = scaleDefault;
    sprite.depth = Layer::MIDDLE;
    sprite.rotation = rotationDefault;
    sprite.xAnchor = 0; // Defina o âncora X no meio (50%) da largura.
    sprite.yAnchor = 0; // Defina o âncora Y no meio (50%) da altura.
}


void Sprite::Draw(float x, float y, float z)
{
    sprite.x = x - sprite.xAnchor;
    sprite.y = y + sprite.yAnchor;
    sprite.depth = z;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(&sprite);
}

// ---------------------------------------------------------------------------------