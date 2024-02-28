//#include "DXUT.h"
//#include "MissionariesCannibalsProblem.h"
#include "Window.h"
#include "DirectXWindow.h"

#include <sstream>

using std::stringstream;

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------



//int UseEngine(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
//	try {
//		// cria motor e configura a janela
//		Engine* engine = Engine::Instance();
//		// configura a janela
//		engine->window->Mode(WINDOWED);
//		engine->window->Size(800, 600);
//		engine->window->Color(1, 1, 0);
//		engine->window->Title("My Game");
//		engine->window->Icon(IDI_ICON);
//		//engine->window->Cursor(IDC_CURSOR);	
//		engine->SetGraphicsFPS(FPS_MONITOR);
//		// aplicação pausa/resume ao perder/ganhar o foco
//		engine->window->LostFocus(Engine::Pause);
//		engine->window->InFocus(Engine::Resume);
//		// cria e executa a aplicação
//		int exitCode = engine->Start(new MissionariesCannibalsProblem());
//
//		// finaliza execução
//		delete engine;
//		return exitCode;
//	}
//	catch (Error& e) {
//		MessageBox(nullptr, e.ToString().data(), "DXGI DXUT", MB_OK);
//		return 0;
//	}
//
//}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	// Crie um objeto DirectXWindow
	DirectXWindow window;

	// Configurar propriedades da janela
	window.Title("DirectX Window Test");
	window.Size(800, 600);
	window.Mode(WINDOWED);

	// Crie a janela
	if (!window.Create()) {
		// Se a criação da janela falhar, exiba uma mensagem de erro e retorne
		MessageBox(NULL, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	// Mostre a janela
	ShowWindow(window.Id(), SW_SHOW);

	// Inicie o loop de mensagens
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// Adicione um caso para a mensagem de destruição da janela
		if (msg.message == WM_DESTROY) {
			break; // Sai do loop quando a janela for fechada
		}
	}

	return EXIT_SUCCESS;
}
//OutputDebugString(s.str().c_str());
