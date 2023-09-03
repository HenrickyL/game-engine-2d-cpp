#include "Engine.h"
#include <windows.h>
#include <sstream>
#include "Error.h"
using std::stringstream;

// ------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe
Game*		Engine::game			= nullptr;			// apontadador da aplicação
Window*		Engine::window		= nullptr;			// janela da aplicação
Graphics*	Engine::graphics	= nullptr;			// dispositivo gráfico
Engine*		Engine::instance	= nullptr;			// dispositivo gráfico
float		Engine::frameTime	= 0.0f;				// tempo do quadro atual
Input*		Engine::input		= nullptr;			// dispositivos de entrada
bool		Engine::paused		= false;			// estado do motor
bool		Engine::onGraphics	= true;				// estado do motor
Renderer*	Engine::renderer	= nullptr;     // renderizador de sprites 
Timer		Engine::timer;                      // medidor de tempo
// ------------------------------------------------------------------------------
Engine::Engine()
{
	window = new Window();
	graphics = new Graphics(window);
	renderer = new Renderer();
}
// ------------------------------------------------------------------------------

 Engine* Engine::Instance() {
	if (Engine::instance == nullptr) {
		Engine::instance = new Engine();
	}
	return Engine::instance;
}

// ------------------------------------------------------------------------------

Engine::~Engine()
{
	delete game;
	delete renderer;
	delete graphics;
	delete input;
	delete window;
}
// ------------------------------------------------------------------------------
int Engine::Start(Game* level)
{
	game = level;

	// cria janela do jogo
	window->Create();

	// inicializa dispositivos de entrada (deve ser feito após criação da janela)
	input = new Input();

	// inicializa dispositivo gráfico
	if (!graphics->Initialize())
	{
		MessageBox(window->Id(), "Falha na inicialização do dispositivo gráfico", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// inicializa renderizador de sprites
	if (!renderer->Initialize(window, graphics))
	{
		MessageBox(window->Id(), "Falha na criação do renderizador", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// altera a window procedure da janela ativa para EngineProc
	SetWindowLongPtr(window->Id(), GWLP_WNDPROC, (LONG_PTR)EngineProc);

	// ajusta a resolução do Sleep para 1 milisegundo
	// requer uso da biblioteca winmm.lib
	timeBeginPeriod(1);

	int exitCode = Loop();

	// volta a resolução do Sleep ao valor original
	timeEndPeriod(1);

	return exitCode;
}
// -------------------------------------------------------------------------------

int Engine::Loop()
{
	// inicia contagem de tempo
	timer.Start();

	// mensagens do Windows
	MSG msg = { 0 };

	// inicialização da aplicação
	game->Init();

	// laço principal
	do
	{
		// trata todos os eventos antes de atualizar a aplicação
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// -----------------------------------------------
			// Pausa/Resume Jogo
			// -----------------------------------------------

			if (input->KeyPress(VK_PAUSE))
			{
				if (paused)
					Resume();
				else
					Pause();
			}

			// -----------------------------------------------
			if (!paused) {
				// calcula o tempo do quadro
				frameTime = FrameTime();

				// atualização da aplicação 
				game->Update();

				if (onGraphics) {
					// limpa a tela para o próximo quadro
					graphics->Clear();

					// desenho da aplicação
					game->Draw();

					// renderiza sprites
					renderer->Render();

					// apresenta o jogo na tela (troca backbuffer/frontbuffer)
					graphics->Present();
				}
				else {
					game->Draw();
				}
			}
			else {

				game->OnPause();

				// renderiza sprites
				renderer->Render();
				// apresenta o jogo na tela (troca backbuffer/frontbuffer)
				graphics->Present();
			}
		}

	} while (msg.message != WM_QUIT);

	// finalização do aplicação
	game->Finalize();

	// encerra aplicação
	return int(msg.wParam);
}

// -----------------------------------------------------------------------------

float Engine::FrameTime()
{

#ifdef _DEBUG
	// ----- START DEBUG ----------
	static float totalTime = 0.0f;	// tempo total transcorrido 
	static uint  frameCount = 0;	// contador de frames transcorridos
	// ------ END DEBUG -----------
#endif

	// tempo do frame atual
	frameTime = timer.Reset();

#ifdef _DEBUG
	// ----- START DEBUG ----------
	// tempo acumulado dos frames
	totalTime += frameTime;

	// incrementa contador de frames
	frameCount++;

	// a cada 1000ms (1 segundo) atualiza indicador de FPS na janela
	if (totalTime >= 1.0f)
	{
		stringstream text;			// fluxo de texto para mensagens
		text << std::fixed;			// sempre mostra a parte fracionária
		text.precision(3);			// três casas depois da vírgula

		text << window->Title().c_str() << "    "
			<< "FPS: " << frameCount << "    "
			<< "Frame Time: " << frameTime * 1000 << " (ms)";

		SetWindowText(window->Id(), text.str().c_str());

		frameCount = 0;
		totalTime -= 1.0f;
	}
	// ------ END DEBUG -----------
#endif

	return frameTime;
}

// -------------------------------------------------------------------------------

LRESULT CALLBACK Engine::EngineProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// janela precisa ser repintada
	if (msg == WM_PAINT) {
	}
	return CallWindowProc(Input::InputProc, hWnd, msg, wParam, lParam);
}

// -----------------------------------------------------------------------------
