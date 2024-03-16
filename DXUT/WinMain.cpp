#include "DXUT.h"
#include "MissionariesCannibalsProblem.h"
#include "DXWindow.h"
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

struct Obj {
	int x = 0;
	int y = 0;
};


void drawTriangle(Obj pos) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(pos.x,		pos.y+0.5, 0.0);
	glVertex3f(pos.x+0.5,	pos.y -0.5, 0.0);
	glVertex3f(pos.x-0.5,	pos.y -0.5, 0.0);
	glEnd();
}

void drawQuad(Obj pos) {
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_QUADS);
	glVertex3f(pos.x-2.5,pos.y -2.5, 0);
	glVertex3f(pos.x+2.5,pos.y -2.5, 0);
	glVertex3f(pos.x+2.5, pos.y+ 2.5, 0);
	glVertex3f(pos.x-2.5,pos.y+ 2.5, 0);
	glEnd();
}

int GLWindowTest() {

	GLWindow window;
	window.Create();
	window.SetColor(Color(0.0,0.15,0.35));
	auto win = window.GetWindow();

	bool onMode = true;

	std::vector<void (*)(Obj)> functionVector;
	int index = 0;
	functionVector.push_back(drawQuad);
	functionVector.push_back(drawTriangle);
	Obj obj;

	//projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.f, 10.f, -10.f, 10.f, 1.f, -1.f);

	while (!window.ShouldClose()) {
		// Processa eventos
		glfwPollEvents();
		if (Input::KeyDown(ESCAPE)) {
			glfwSetWindowShouldClose(win, GLFW_TRUE);
		}

		if (Input::KeyPress(BACKSPACE)) {
			//Contorno - posso usar para mostrar a malha
			if (onMode) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			onMode = !onMode;
		}

		if (Input::KeyPress(LEFT)) {
			Position p = Input::MousePosition();
			Position p2 = Input::MouseClick();

			short w = Input::MouseWheel();
			bool click = Input::OnClick();
			bool aaa = Input::OnDrag();
			int x = Input::DragX();
			int y = Input::DragY();

			obj.x -= 1;
		}

		if (Input::MouseWheel() != 0) {
			obj.y = Input::MouseWheel();
		}

		if (Input::KeyPress(RIGHT)) {
			obj.x += 1;
		}

		if (Input::KeyPress(SPACE)) {
			index++;
			if (index >= functionVector.size()) {
				index = 0;
			}
		}

		// Renderização aqui
		window.Clear();

		functionVector[index](obj);

		// Troca os buffers
		window.SwapBuffers();
	}
	window.Close();
	return 0;
}




int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	
	return GLWindowTest();

	//return UseEngine( hInstance, hPrevInstance,lpCmdLine,  nCmdShow);

	
}
//OutputDebugString(s.str().c_str());
