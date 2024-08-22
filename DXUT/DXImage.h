#ifndef DX_IMAGE_H
#define DX_IMAGE_H

#include "Image.h"
#include <d3d11.h>
#include "DX_Texture_Util.h"

class DXImage : public Image {
private:
	ID3D11ShaderResourceView* _textureView;

public:
    DXImage(const string& filename);
    ~DXImage();

    ID3D11ShaderResourceView* textureView() const;
    void SetView(ID3D11ShaderResourceView* value);

    void Load(const string& filename) override;
    void Release() override;
};
#endif