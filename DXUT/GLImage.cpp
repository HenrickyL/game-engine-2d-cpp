#include "GLImage.h"
#include <stdexcept>


GLImage::GLImage(const string& _filename_) : Image(_filename_), _textureID(0) {
    Load(_filename_);
}

GLImage::~GLImage() {
    Release();
}



void GLImage::Load(const string& filename) {
    glGenTextures(1, &_textureID);
    LoadTexture(_textureID, filename);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
}

void GLImage::Release() {
    if (_textureID) {
        glDeleteTextures(1, &_textureID);
        _textureID = 0;
    }
}


GLuint GLImage::TextureID() const { return _textureID; }


void GLImage::LoadTexture(GLuint tex_id, std::string filePath) const {

    unsigned char* imgData;
    int w, h, channels;

    stbi_set_flip_vertically_on_load(true);
    imgData = stbi_load(filePath.c_str(), &w, &h, &channels, 4);
    if (imgData)
    {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(imgData);
    }
    else {
        throw std::runtime_error("Fail to Load Texture");
    }
}
