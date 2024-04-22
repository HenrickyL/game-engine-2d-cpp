// GLGraphics.h
#ifndef UT_GLGRAPHICS_H
#define UT_GLGRAPHICS_H

#include "Graphics.h"
//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLWindow.h"

class GLGraphics : public Graphics {
private:
    void set3DRenderContext() const;
    void set2DRenderContext() const;
public:
    GLGraphics(GLWindow* window);
    ~GLGraphics();

    void VSync(bool state) override;
    void Clear() override;
    void Present() override;
    bool Initialize() override;
    
};

#endif // GLGRAPHICS_H
