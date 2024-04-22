#include "DXUT.h"
#include "MissionariesCannibalsProblem.h"
#include "DXWindow.h"
#include "GLWindow.h"
#include "Geometry.h"
#include "GLDrawGeometry.h"
#include "GLCamera.h"
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
		engine->window->SetColor(Color(0.0, 0.15, 0.35));
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
	float z = -25;
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


void DrawRect(float p1[3], float p2[3], float p3[3], float p4[3] , Color c) {
	float cs[3] = { c.r(), c.g(), c.b() };
	glColor3fv(cs);
	glBegin(GL_QUADS);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
	glEnd();
}

void drawCube(Position pos, float size = 2.5f) {
	float d = size / 2;
	glColor3f(1.f, 0.f, 0.f);
	float v1[3] = { pos.x() - d,		pos.y() + d,	pos.z() + d};
	float v2[3] = { pos.x() -d,			pos.y() -d,		pos.z() + d };
	float v3[3] = { pos.x() +  d,		pos.y() -d,		pos.z() + d };
	float v4[3] = { pos.x() +  d,		pos.y() +d,		pos.z() + d };
	float v5[3] = { pos.x() +  d,		pos.y() +d,		pos.z() -d };
	float v6[3] = { pos.x() +  d,		pos.y() -d,		pos.z() -d };
	float v7[3] = { pos.x() -d,			pos.y() -d,		pos.z() -d };
	float v8[3] = { pos.x() -d,			pos.y() +d,		pos.z() -d };
	

	//frente
	DrawRect(v1, v2, v3, v4, Color::RED);

	DrawRect(v4, v3, v6, v5, Color::BLUE);

	DrawRect(v5, v8, v7, v6, Color::GREEN);

	DrawRect(v1, v8, v7, v2, Color::YELLOW);

	DrawRect(v1, v4, v5, v8, Color::MAGENTA);

	DrawRect(v2, v7, v6, v3, Color::WHITE);

}

int GLWindowTest() {

	GLWindow window;
	window.Create();
	window.SetColor(Color(0.0,0.15,0.35));
	auto win = window.GetWindow();

	Timer timer;
	timer.Start();
	float offsetTimer = 0.05;

	GLCamera cam1(Position(0,0,5));
	GLCamera cam2(Position(0, 0, 5));

	GLCamera* cam = &cam1;


	bool onMode = true;

	std::vector<void (*)(Obj)> functionVector;
	int index = 0;

	functionVector.push_back(drawQuad);
	functionVector.push_back(drawTriangle);
	
	Geometry* obj;
	Rect r(Position(0,0,0), 1, 1);
	Rect r2(Position(-0.5, 0, 0), 1, 1);
	Rect r3(Position(0.5, 0, 0), 1, 1);


	Rect rects[3] = { r, r2, r3 };

	Rect selected = r;
	r.RotationZ(1);
	GLDrawGeometry drawner;
	float delta = 0.1;

	Point p;
	p.setSize(1);

	Line l(Position(-1,0), Position(1,0.5));
	l.setStroke(5);

	Circle c = Circle(Position(1,0), 1);
	c.setStroke(3);


	Poly poly;
	poly.setStroke(3);
	poly.addVertex(Position(0, 0.5));
	poly.addVertex(Position(0.5, -0.5));
	poly.addVertex(Position(-0.5, -0.5));

	obj = &poly;

	Point center = Point(obj->position());
	center.setSize(10);


	std:string s = "";

	float globalRotation = 0;


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

		if (Input::KeyDown(KEY_A)) {
			globalRotation -= 5;
		}

		if (Input::KeyDown(KEY_D)) {
			globalRotation += 5;
		}

		if (Input::KeyDown(LEFT) && timer.Elapsed(offsetTimer)) {
			cam->TranslateTo(Vector::Left * delta);

			timer.Reset();
		}
		if (Input::KeyDown(RIGHT) && timer.Elapsed(offsetTimer)) {
			cam->TranslateTo(Vector::Right * delta);
			timer.Reset();

		}
		if (Input::KeyDown(UP) && timer.Elapsed(offsetTimer)) {
			cam->TranslateTo(Vector::Backward*delta);
			timer.Reset();

		}
		if (Input::KeyDown(DOWN) && timer.Elapsed(offsetTimer)) {
			cam->TranslateTo(Vector::Forward*delta);
			timer.Reset();
		}

		if (Input::OnDrag() && timer.Elapsed(offsetTimer)) {
			Position mp = Input::MousePosition();
			float x = mp.x();
			float y = mp.y();
			
			Position current = Position(x - window.Width()/2, y- window.Height()/2);

			Vector d = Position::Zero - current;
			if(d.Magnitude() != 0)
			cam->TranslateLookAt(d.Unit() * delta);
			timer.Reset();
		}


		if (Input::OnWheel()) {
			int dir = Input::MouseWheelDirection();
			if(dir != 0)
				cam->TranslateTo((dir > 0 ? Vector::Up : Vector::Down) *delta);
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
		
		glLoadIdentity();

		cam->Update();


		glTranslatef(0, 0, 0);
		glRotatef(globalRotation, 0, 0, 1);

		/*float w = window.Width();
		float h = window.Height();
		float aspect = window.Aspect();

		Position ppp = Input::MousePosition();

		Position local = Position(ppp.x()/w, -ppp.y()/h);

		p.MoveTo(local*aspect);

		s = "Pos( x:  " + std::to_string(ppp.x()) + "y: " + std::to_string(ppp.y()) + "z: " + std::to_string(ppp.z()) + ")\n";
		OutputDebugString(s.c_str());
		ppp = local;
		s = "PosObj( x:  " + std::to_string(ppp.x()) + "y: " + std::to_string(ppp.y()) + "z: " + std::to_string(ppp.z()) + ")\n";
		OutputDebugString(s.c_str());*/

		
		drawCube(Position::Zero);
		/*drawner.Draw(r);
		drawner.Draw(r2);
		drawner.Draw(r3);*/
		//drawner.Draw(Point());
		//drawner.Draw(center);
		//drawner.Draw(*obj);



		// Troca os buffers
		window.SwapBuffers();
	}
	window.Close();
	return 0;
}




int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	
	//return GLWindowTest();

	return UseEngine( hInstance, hPrevInstance,lpCmdLine,  nCmdShow);

	
}
//OutputDebugString(s.str().c_str());
