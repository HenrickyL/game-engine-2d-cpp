#include "DXUT.h"
#include "MissionariesCannibalsProblem.h"
#include "DXWindow.h"
#include "GLWindow.h"

#include <sstream>
#include <vector>
#include <GLFW/glfw3.h>
#include <math.h>
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
	float z =0;
};


void drawTriangle(Obj pos) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(pos.x,		pos.y+0.5, pos.z);
	glVertex3f(pos.x+0.5,	pos.y -0.5, pos.z);
	glVertex3f(pos.x-0.5,	pos.y -0.5, pos.z);
	glEnd();
}

void drawQuad(Obj pos) {
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_QUADS);
	glVertex3f(pos.x-2.5,pos.y -2.5, pos.z);
	glVertex3f(pos.x+2.5,pos.y -2.5, pos.z);
	glVertex3f(pos.x+2.5, pos.y+ 2.5, pos.z);
	glVertex3f(pos.x-2.5,pos.y+ 2.5, pos.z);
	glEnd();
}


void Rect(float p1[3], float p2[3], float p3[3], float p4[3] , Color c) {
	float cs[3] = { c.r(), c.g(), c.b() };
	glColor3fv(cs);
	glBegin(GL_QUADS);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
	glEnd();
}
void drawCube(Obj pos, float size = 2.5f) {
	float d = size / 2;
	glColor3f(1.f, 0.f, 0.f);
	float v1[3] = { pos.x -d,		pos.y +d,		pos.z + d };
	float v2[3] = { pos.x -d,		pos.y -d,		pos.z + d };
	float v3[3] = { pos.x +  d,		pos.y -d,		pos.z + d };
	float v4[3] = { pos.x +  d,		pos.y +d,		pos.z + d };
	float v5[3] = { pos.x +  d,		pos.y +d,		pos.z -d };
	float v6[3] = { pos.x +  d,		pos.y -d,		pos.z -d };
	float v7[3] = { pos.x -d,		pos.y -d,		pos.z -d };
	float v8[3] = { pos.x -d,		pos.y +d,		pos.z -d };
	

	//frente
	Rect(v1, v2, v3, v4, Color::RED);

	Rect(v4, v3, v6, v5, Color::BLUE);

	Rect(v5, v8, v7, v6, Color::GREEN);

	Rect(v1, v8, v7, v2, Color::YELLOW);

	Rect(v1, v4, v5, v8, Color::MAGENTA);

	Rect(v2, v7, v6, v3, Color::WHITE);

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


	while (!window.ShouldClose()) {
		// Processa eventos
		window.PollEvents();
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
		if (Input::KeyPress(KEY_G)) {
			window.isResizeable(true);
		}

		if (Input::KeyPress(LEFT)) {
			obj.x -= 1;
		}

		if (Input::KeyPress(RIGHT)) {
			obj.x += 1;
		}
		if (Input::KeyPress(UP)) {
			obj.y += 1;
		}
		if (Input::KeyPress(DOWN)) {
			obj.y -= 1;
		}

		if (Input::OnDrag()) {
			Vector d = Input::Drag();
			glLoadIdentity();
			glTranslated(0, 0, -25);
			glRotated(d.x(), 1, 0, 0);
			glRotated(d.y(), 0, 1, 0);

		}

		if (Input::MouseWheel() != 0) {
			float aux = obj.z;
			float value = Input::MouseWheel() * 0.5;
			obj.z = value == 0 ? aux :  value;
		}

		

		if (Input::KeyPress(SPACE)) {
			index++;
			if (index >= functionVector.size()) {
				index = 0;
			}
		}

		// Renderização aqui
		window.Clear();

		//functionVector[index](obj);
		


		drawCube(obj);

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
