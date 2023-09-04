#include "Sprite.h"
#include "Engine.h"
// -------------------------------------------------------------------------------
// Inicialização de membros estáticos das classes
const float Layer::FRONT    = 0.00f;
const float Layer::UPPER    = 0.25f;
const float Layer::MIDDLE   = 0.50f;
const float Layer::LOWER    = 0.75f;
const float Layer::BACK     = 0.99f;
// ---------------------------------------------------------------------------------

Sprite::Sprite(string filename)
{
    // carrega imagem
    image = new Image(filename);
    localImage = true;
    _position = new Point();
    sprite.position = _position;
    // configura registro sprite
    ResetSprite();
}

// ---------------------------------------------------------------------------------

Sprite::Sprite(Image* img)
{
    // aponta para imagem externa
    image = img;
    localImage = false;
    _position = new Point();
    sprite.position = _position;

    // configura registro sprite
    ResetSprite();

}

// ---------------------------------------------------------------------------------

Sprite::~Sprite()
{
    delete _position;
    if (localImage)
        delete image;
}

// ---------------------------------------------------------------------------------


void Sprite::ResetSprite()
{
    sprite.texture = image->View();
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.scale = scaleDefault;
    sprite.depth = Layer::MIDDLE;
    sprite.rotation = rotationDefault;
    sprite.anchorX = Width() / 2;
    sprite.anchorY = Height() / 2;
}


void Sprite::Draw()
{
    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(&sprite);
}

// ---------------------------------------------------------------------------------

void Sprite::SetImage(Image* img)
{
    if (img->Filename() != image->Filename()) {
        image = img;
        sprite.texture = image->View();
        sprite.width = image->Width();
        sprite.height = image->Height();
    }
}

// ---------------------------------------------------------------------------------

void Sprite::SetImage(const std::string _filename)
{
    if (_filename != image->Filename()) {
        image = new Image(_filename);
        sprite.texture = image->View();
        sprite.width = image->Width();
        sprite.height = image->Height();
    }
}

// ---------------------------------------------------------------------------------

void Sprite::SetPosition(const Point p)
{
    _position->MoveTo(p);
}
