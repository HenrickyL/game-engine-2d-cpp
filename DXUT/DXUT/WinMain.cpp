#include "DXUT.h"
#include "WinApp.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	try {
		// cria motor e configura a janela
		Engine* engine = new Engine();
		// configura a janela
		engine->window->Mode(WINDOWED);
		engine->window->Size(1024, 600);
		engine->window->Color(0, 122, 204);
		engine->window->Title("Aplicação Windows");
		engine->window->Icon(IDI_ICON);
		engine->window->Cursor(IDC_CURSOR);

		// aplicação pausa/resume ao perder/ganhar o foco
		engine->window->LostFocus(Engine::Pause);
		engine->window->InFocus(Engine::Resume);

		// cria e executa a aplicação
		int exitCode = engine->Start(new WinApp());

		// finaliza execução
		delete engine;
		return exitCode;
	}
	catch (Error &e) {
		MessageBox(nullptr, e.ToString().data(), "DXGI DXUT", MB_OK);
		return 0;
	}
}