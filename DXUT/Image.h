#ifndef UT_IMAGE_H
#define UT_IMAGE_H
// ---------------------------------------------------------------------------------
#include "types.h"
#include <string>
using std::string;

class Image {
protected:
    uint _width = 0;
    uint _height = 0;
    std::string _filename;

public:
    Image(const string& filename);
    virtual ~Image();
    // retorna largura da imagem
    uint width() const;
    // retorna altura da imagem
    uint height() const;
    std::string filename() const;

    virtual void Load(const string& filename) = 0;
    virtual void Release() = 0;
};
// --------------------------------------------------------------------------------
#endif




