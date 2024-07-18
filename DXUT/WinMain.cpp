#include <sstream>
using std::stringstream;
#include "DXUT.h"
#include "MyGame.h"
#include "Test2d.h"

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------


int UseEngine(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	try {

		bool isTest2d = false;

		// cria motor e configura a janela
		Engine* engine = Engine::Instance();
		engine->SetType(isTest2d ? T_2D : T_3D);
		// configura a janela
		engine->window->Mode(WINDOWED);

		//engine->window->Size(1920, 1080);
		engine->window->Size(1024, 768);
		//engine->window->Size(800, 600);

		engine->window->SetColor(Color(0.0, 0.15, 0.35));
		engine->window->SetTitle(isTest2d ? "test 2d" : "My Game");
		engine->window->Icon(IDI_ICON);
		//engine->window->Cursor(IDC_CURSOR);	
		//engine->SetGraphicsFPS(FPS_MONITOR);
		// aplica��o pausa/resume ao perder/ganhar o foco
		engine->window->LostFocus(Engine::Pause);
		engine->window->InFocus(Engine::Resume);
		// cria e executa a aplica��o

		Game* g;

		if (isTest2d) {
			g = new Test2D();
		}
		else {
			g = new MyGame();
		}
		int exitCode = engine->Start(g);

		// finaliza execu��o
		delete engine;
		return exitCode;
	}
	catch (Error& e) {
		MessageBox(nullptr, e.ToString().data(), "DXGI DXUT", MB_OK);
		return 0;
	}
}



//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <gl/GLU.h>
//
//// Função para inicializar o GLFW
//bool initGLFW() {
//    if (!glfwInit()) {
//        return false;
//    }
//    return true;
//}
//
//// Função para inicializar o GLEW
//bool initGLEW() {
//    glewExperimental = GL_TRUE; // Para usar as funcionalidades modernas do GLEW
//    GLenum err = glewInit();
//    if (err != GLEW_OK) {
//        return false;
//    }
//    return true;
//}
//
//// Função para desenhar o cubo
//void drawCube() {
//    glBegin(GL_QUADS);
//
//    // Face frontal
//    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
//    glVertex3f(-0.5f, -0.5f, 0.5f);
//    glVertex3f(0.5f, -0.5f, 0.5f);
//    glVertex3f(0.5f, 0.5f, 0.5f);
//    glVertex3f(-0.5f, 0.5f, 0.5f);
//
//    // Face traseira
//    glColor3f(0.0f, 1.0f, 0.0f); // Verde
//    glVertex3f(-0.5f, -0.5f, -0.5f);
//    glVertex3f(0.5f, -0.5f, -0.5f);
//    glVertex3f(0.5f, 0.5f, -0.5f);
//    glVertex3f(-0.5f, 0.5f, -0.5f);
//
//    // Face esquerda
//    glColor3f(0.0f, 0.0f, 1.0f); // Azul
//    glVertex3f(-0.5f, -0.5f, -0.5f);
//    glVertex3f(-0.5f, -0.5f, 0.5f);
//    glVertex3f(-0.5f, 0.5f, 0.5f);
//    glVertex3f(-0.5f, 0.5f, -0.5f);
//
//    // Face direita
//    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
//    glVertex3f(0.5f, -0.5f, -0.5f);
//    glVertex3f(0.5f, -0.5f, 0.5f);
//    glVertex3f(0.5f, 0.5f, 0.5f);
//    glVertex3f(0.5f, 0.5f, -0.5f);
//
//    // Face superior
//    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
//    glVertex3f(-0.5f, 0.5f, 0.5f);
//    glVertex3f(0.5f, 0.5f, 0.5f);
//    glVertex3f(0.5f, 0.5f, -0.5f);
//    glVertex3f(-0.5f, 0.5f, -0.5f);
//
//    // Face inferior
//    glColor3f(0.0f, 1.0f, 1.0f); // Ciano
//    glVertex3f(-0.5f, -0.5f, 0.5f);
//    glVertex3f(0.5f, -0.5f, 0.5f);
//    glVertex3f(0.5f, -0.5f, -0.5f);
//    glVertex3f(-0.5f, -0.5f, -0.5f);
//
//    glEnd();
//}
//
//int test() {
//    if (!initGLFW()) return -1;
//
//    float w = 1024;
//    float h = 768;
//
//    GLFWwindow* window = glfwCreateWindow(w, h, "Cubo 3D com OpenGL", nullptr, nullptr);
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }
//
//
//    glfwMakeContextCurrent(window);
//    glViewport(0, 0, w, h);
//
//    gluOrtho2D(0, w, 0, h);
//
//    if (!initGLEW()) return -1;
//
//    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade
//
//    glfwSwapInterval(1); // Habilita v-sync para limitar a taxa de quadros
//
//    while (!glfwWindowShouldClose(window)) {
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // Definir a matriz de projeção
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
//
//        // Definir a matriz de visualização
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//        gluLookAt(0.0, 0.0, 2.0,  // Posição da câmera
//            0.0, 0.0, 0.0,  // Ponto de observação
//            0.0, 1.0, 0.0); // Vetor "up"
//
//        drawCube();
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}



int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

    return UseEngine( hInstance, hPrevInstance,lpCmdLine,  nCmdShow);
    //return test();
}
//OutputDebugString(s.str().c_str());


