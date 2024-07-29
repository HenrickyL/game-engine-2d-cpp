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

		bool isTest2d = true;

		// cria motor e configura a janela
		Engine* engine = Engine::Instance();
		engine->SetType(isTest2d ? T_2D : T_3D);
		// configura a janela
		engine->window->Mode(WINDOWED);

		//engine->window->Size(1920, 1080);
		//engine->window->Size(1024, 768);
		engine->window->Size(1366, 768);
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

void redimensiona(int w, int h)
{
	glViewport(0, 0, w, h);

	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0, 1.0, -1.0);
	else
		glOrtho(-10.0, 10.0, -10.0 / aspect, 10.0 / aspect, 1.0, -1.0);
}


void desenha()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-2.5, -2.5, 0.0);
	glVertex3f(2.5, -2.5, 0.0);
	glVertex3f(2.5, 2.5, 0.0);
	glVertex3f(-2.5, 2.5, 0.0);
	glEnd();
}


int test() {
	const int LARGURA = 800;
	const int ALTURA = 600;

	/* Initialize the library */
	glfwInit();

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(LARGURA, ALTURA, "Desenha Quadrado", NULL, NULL);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// -- inicio
	glClearColor(0.0, 0.15, 0.25, 1.0); // cor de fundo


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

		redimensiona(largura, altura);

		desenha();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

    return UseEngine( hInstance, hPrevInstance,lpCmdLine,  nCmdShow);
    //return test();
}
//OutputDebugString(s.str().c_str());


