#include "Image.h"
#include "Graphics.h"

// -------------------------------------------------------------------------------

Image::Image(string _filename) : textureView(nullptr), width(0), height(0)
{
    filename = _filename;
    // cria sharer resource view da imagem em disco
    D3D11CreateTextureFromFile(
        Graphics::device,               // dispositivo Direct3D
        Graphics::context,              // contexto do dispositivo
        _filename.c_str(),               // nome do arquivo de imagem
        nullptr,                        // retorna textura 
        &textureView,                   // retorna view da textura
        width,                          // retorna largura da imagem
        height);                        // retorna altura da imagem
}

// -------------------------------------------------------------------------------

Image::~Image()
{
    // libera mem�ria ocupada pela texture view
    if (textureView)
    {
        // pega ponteiro para recurso
        ID3D11Resource* resource = nullptr;
        textureView->GetResource(&resource);

        // liberando a view n�o libera automaticamente
        // o recurso que foi criado junto com a view
        if (resource)
        {
            resource->Release();
            resource = nullptr;
        }

        textureView->Release();
        textureView = nullptr;
    }
}

// -------------------------------------------------------------------------------