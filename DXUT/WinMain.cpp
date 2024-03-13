#include "DXUT.h"
#include "MissionariesCannibalsProblem.h"
#include "DirectXWindow.h"
#include "GLWindow.h"

#include <sstream>
#include <vector>
#include <GLFW/glfw3.h>
using std::stringstream;

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------


int UseEngine(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	try {
		// cria motor e configura a janela
		Engine* engine = Engine::Instance();
		// configura a janela
		engine->window->Mode(WINDOWED);
		engine->window->Size(800, 600);
		engine->window->SetColor(Color(1, 1, 0));
		engine->window->Title("My Game");
		engine->window->Icon(IDI_ICON);
		//engine->window->Cursor(IDC_CURSOR);	
		engine->SetGraphicsFPS(FPS_MONITOR);
		// aplicação pausa/resume ao perder/ganhar o foco
		engine->window->LostFocus(Engine::Pause);
		engine->window->InFocus(Engine::Resume);
		// cria e executa a aplicação
		int exitCode = engine->Start(new MissionariesCannibalsProblem());

		// finaliza execução
		delete engine;
		return exitCode;
	}
	catch (Error& e) {
		MessageBox(nullptr, e.ToString().data(), "DXGI DXUT", MB_OK);
		return 0;
	}
}


void drawTriangle() {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();
}

void drawQuad() {
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_QUADS);
	glVertex3f(-2.5, -2.5, 0);
	glVertex3f(2.5, -2.5, 0);
	glVertex3f(2.5, 2.5, 0);
	glVertex3f(-2.5, 2.5, 0);
	glEnd();
}

int GLWindowTest() {

	GLWindow window;
	window.Create();
	window.SetColor(Color(0.0,0.15,0.35));
	auto win = window.GetWindow();

	bool onMode = true;

	std::vector<void (*)()> functionVector;
	int index = 0;
	functionVector.push_back(drawTriangle);
	functionVector.push_back(drawQuad);


	//projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.f, 10.f, -10.f, 10.f, 1.f, -1.f);


	while (!window.ShouldClose()) {
		// Processa eventos
		glfwPollEvents();
		if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(win, GLFW_TRUE);
		}

		if (glfwGetKey(win, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
			//Contorno - posso usar para mostrar a malha
			if (onMode) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			onMode = !onMode;
		}

		if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS) {
			index++;
			if (index >= functionVector.size()) {
				index = 0;
			}
		}

		// Renderização aqui
		window.Clear();

		functionVector[index]();

		// Troca os buffers
		window.SwapBuffers();
	}
	window.Close();
	return 0;
}




int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	
	return GLWindowTest();

	//return UseEngine( hInstance, hPrevInstance,
	//	lpCmdLine,  nCmdShow);

	
}
//OutputDebugString(s.str().c_str());
