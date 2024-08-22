#include "DXImage.h"
#include "DXGraphics.h"

DXImage::DXImage(const string& filename) : Image(filename), _textureView(nullptr) {
    Load(filename);
}

DXImage::~DXImage() {
    Release();
}


void DXImage::Load(const string& filename) {
    D3D11CreateTextureFromFile(
        DXGraphics::device,
        DXGraphics::context,
        filename.c_str(),
        nullptr,
        &_textureView,
        _width,
        _height
    );
}

void DXImage::Release() {
    if (_textureView) {
        ID3D11Resource* resource = nullptr;
        _textureView->GetResource(&resource);
        if (resource) {
            resource->Release();
            resource = nullptr;
        }
        _textureView->Release();
        _textureView = nullptr;
    }
}

ID3D11ShaderResourceView* DXImage::textureView() const { return _textureView; }

void DXImage::SetView(ID3D11ShaderResourceView* value) { _textureView = value; }
