#include "DXUT.h"
#include "MissionariesCannibalsProblem.h"
#include "DirectXWindow.h"
#include <sstream>

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
		engine->window->Color(1, 1, 0);
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




int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	// Inicializar GLFW
	if (!glfwInit()) {
		// Se a inicialização falhar, exibir uma mensagem de erro e encerrar
		MessageBox(nullptr, "Failed to initialize GLFW", "Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	// Criar uma janela GLFW
	GLFWwindow* window = glfwCreateWindow(800, 600, "Minha Janela GLFW", nullptr, nullptr);
	if (!window) {
		// Se a criação da janela falhar, exibir uma mensagem de erro e encerrar
		MessageBox(nullptr, "Failed to create GLFW window", "Error", MB_OK | MB_ICONERROR);
		glfwTerminate();
		return -1;
	}

	// Definir o contexto da janela como o contexto atual
	glfwMakeContextCurrent(window);

	// Loop principal
	while (!glfwWindowShouldClose(window)) {
		// Processar eventos
		glfwPollEvents();

		// Renderizar aqui

		// Trocar os buffers
		glfwSwapBuffers(window);
	}

	// Encerrar GLFW
	glfwTerminate();

	return 0;



	/*return UseEngine( hInstance, hPrevInstance,
		lpCmdLine,  nCmdShow);*/

	
}
//OutputDebugString(s.str().c_str());
