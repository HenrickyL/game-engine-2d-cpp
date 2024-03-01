//#include "DXUT.h"
//#include "MissionariesCannibalsProblem.h"
//#include "Window.h"
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
//}


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // Crie uma instância da classe DirectXWindow
    DirectXWindow window;

    // Tente criar a janela usando o método Create()
    if (window.Create()) {
        // A janela foi criada com sucesso
        // Agora você pode adicionar código aqui para interagir com a janela, como desenhar na tela, responder a eventos, etc.

        // Por exemplo, você pode manter a janela aberta até que o usuário a feche:
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    else {
        // A criação da janela falhou
        // Trate o erro de acordo com sua lógica de aplicativo
    }

    return 0;
	
}
//OutputDebugString(s.str().c_str());
