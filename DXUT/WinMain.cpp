#include <sstream>
using std::stringstream;
#include "DXUT.h"
#include "MyGame.h"
#include "Test2d.h"
#include "ShortPathProblem.h"
// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------


int UseEngine(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	try {

		bool isTest2d = true;

		// cria motor e configura a janela
		Engine* engine = Engine::Instance(E_DirectX);
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
			g = new ShortPathProblem();
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



int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

    return UseEngine( hInstance, hPrevInstance,lpCmdLine,  nCmdShow);
    //return test();
}
//OutputDebugString(s.str().c_str());


