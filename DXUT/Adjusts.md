# Adjusts list

## 1. Problema de perspectiva
nos arquivos GLWindow e GLGraphics, ao meu ver o certo seria transferir o codigo de perspectiva do windowSizeCallback para setupPerspectiveContext.
```cpp
//GLWindow.cpp
void GLWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
    glfwSetWindowSize(window, width, height); 
    // Calcula a proporção da janela
    _aspect = (double)width / (double)height;
    glViewport(0, 0, width, height);

    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
}
```

```cpp
bool GLGraphics::Initialize() {
    //...
    
    setupPerspectiveContext();

    //...
}


void GLGraphics::setupPerspectiveContext() const {
    if (_type == T_3D) {
        set3DRenderContext();
    }
    else {
        //set2DRenderContext();
    }
    glMatrixMode(GL_MODELVIEW);
}
```