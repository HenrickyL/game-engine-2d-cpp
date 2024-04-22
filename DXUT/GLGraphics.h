// GLGraphics.h
#ifndef UT_GLGRAPHICS_H
#define UT_GLGRAPHICS_H

#include "Graphics.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

class GLGraphics : public Graphics {
private:
    GLFWwindow* window;
    float viewportWidth;
    float viewportHeight;
    FPSType currentFPS;

public:
    GLGraphics(Window* window);
    ~GLGraphics();

    void VSync(bool state) override;
    void Clear() override;
    void Present() override;
    bool Initialize() override;
    void SetViewportWidth(float width) override;
    void SetViewportHeight(float height) override;
    float ViewportWidth() const override;
    float ViewportHeight() const override;
    void SetFPS(FPSType fps) override;
    FPSType FPS() const override;
};

#endif // GLGRAPHICS_H
