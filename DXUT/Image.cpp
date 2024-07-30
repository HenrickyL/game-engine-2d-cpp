#include "Image.h"

Image::Image(const string& _filename_) : _width(0), _height(0), _filename(_filename_) {}
Image::~Image() {}
// retorna largura da imagem
uint Image::width() const { return _width; }
// retorna altura da imagem
uint Image::height() const { return _height; }
std::string Image::filename() const { return _filename; }
