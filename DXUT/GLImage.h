#ifndef GL_IMAGE_H
#define GL_IMAGE_H

#include "Image.h"
#include <GL/glew.h>
#include "stb_Image.h"

class GLImage : public Image {
private:
    GLuint _textureID;
    int _channels = 0;

    void LoadTexture(GLuint tex_id, std::string filePath) const;

public:
    GLImage(const string& filename);
    ~GLImage();

    void Load(const string& filename) override;
    void Release() override;
    GLuint TextureID() const;
};

#endif // GL_IMAGE_H
