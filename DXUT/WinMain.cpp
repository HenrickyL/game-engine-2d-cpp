#include "DXUT.h"
#include "MyGame.h"
#include <sstream>
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
		engine->window->Mode(FULLSCREEN);
		engine->window->Size(1280, 1024);
		engine->window->SetColor(Color(0.0, 0.15, 0.35));
		engine->window->SetTitle("My Game");
		engine->window->Icon(IDI_ICON);
		//engine->window->Cursor(IDC_CURSOR);	
		//engine->SetGraphicsFPS(FPS_MONITOR);
		// aplica��o pausa/resume ao perder/ganhar o foco
		engine->window->LostFocus(Engine::Pause);
		engine->window->InFocus(Engine::Resume);
		// cria e executa a aplica��o
		int exitCode = engine->Start(new MyGame());

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

	
}
//OutputDebugString(s.str().c_str());
