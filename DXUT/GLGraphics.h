// GLGraphics.h
#ifndef UT_GLGRAPHICS_H
#define UT_GLGRAPHICS_H

#include "GLWindow.h"
#include "Graphics.h"

class GLGraphics : public Graphics {
private:
    void set3DRenderContext() const;
    void set2DRenderContext() const;
    void setupPerspectiveContext() const;
public:
    GLGraphics(GLWindow* window);
    ~GLGraphics();

    void VSync(bool state) override;
    void Clear() override;
    void Present() override;
    bool Initialize() override;
};

#endif // GLGRAPHICS_H
