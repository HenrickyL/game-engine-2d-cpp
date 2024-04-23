#include "Engine.h"

#include <windows.h>
#include <sstream>
#include <thread>

#include "Error.h"

#include "DXWindow.h"
#include "DXInput.h"
#include "DXGraphics.h" 

#include "GLWindow.h"
#include "GLInput.h"
#include "GLGraphics.h" 

using std::stringstream;


// ------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe
Game*		Engine::game		= nullptr;			// apontadador da aplicação
Window*		Engine::window		= nullptr;			// janela da aplicação
Engine*		Engine::instance	= nullptr;			// dispositivo gráfico
float		Engine::_frameTime	= 0.0f;				// tempo do quadro atual
bool		Engine::paused		= false;			// estado do motor
bool		Engine::onGraphics	= true;				// estado do motor
//Renderer*	Engine::renderer	= nullptr;     // renderizador de sprites 
Timer		Engine::timer;                      // medidor de tempo
// ------------------------------------------------------------------------------
Engine::Engine()
{
	_context = context();
	Engine::window = _context->window();
	//renderer = new Renderer();
}

// ------------------------------------------------------------------------------

GraphicContext* Engine::context(){
	return getContextByType(_graphicType);
}


GraphicContext* Engine::getContextByType(EngineGraphicsType type) {
	if (_graphicType == E_OpenGL) {
		GLWindow* _window = new GLWindow();
		GLGraphics* graphics = new GLGraphics(_window);

		if (!_contextGL)
			_contextGL = new GraphicContext(graphics, _window);
		return _contextGL;
	}
	else {
		DXWindow* _window = new DXWindow();
		DXGraphics* graphics = new DXGraphics(_window);

		if (!_contextDX)
			_contextDX = new GraphicContext(graphics, _window);
		return _contextDX;
	}
}



void Engine::SetGraphicType(EngineGraphicsType value) { 
	this->_graphicType = value; 

	_context = getContextByType(value);
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
	//delete renderer;

	if(_contextDX) delete _contextDX;
	if(_contextGL) delete _contextGL;
}

// ------------------------------------------------------------------------------
int Engine::Start(Game* level)
{
	game = level;
	
	Window * _window = _context->window();
	_window->Create();

	Graphics* graphics = _context->graphics();


	// inicializa dispositivo gráfico
	if (!graphics->Initialize())
	{
		MessageBox(_window->Id(), "Falha na inicialização do dispositivo gráfico", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// inicializa renderizador de sprites
	/*if (!renderer->Initialize(window, graphics))
	{
		MessageBox(window->Id(), "Falha na criação do renderizador", "Engine", MB_OK);
		return EXIT_FAILURE;
	}*/

	// altera a window procedure da janela ativa para EngineProc
	//SetWindowLongPtr(window->Id(), GWLP_WNDPROC, (LONG_PTR)EngineProc);

	// ajusta a resolução do Sleep para 1 milisegundo
	// requer uso da biblioteca winmm.lib
	timeBeginPeriod(1);

	int exitCode = Loop();

	// volta a resolução do Sleep ao valor original
	timeEndPeriod(1);

	_window->Close();

	return exitCode;
}
// -------------------------------------------------------------------------------

int Engine::Loop()
{
	// inicia contagem de tempo
	timer.Start();

	// mensagens do Windows
	MSG msg = { 0 };

	Window* _window = _context->window();
	Graphics* graphics = _context->graphics();


	// inicialização da aplicação
	game->Init();

	// laço principal
	while (!_window->ShouldClose())
	{
		_window->PollEvents();

		if (Input::KeyPress(PAUSE))
		{
			if (paused)
				Resume();
			else
				Pause();
		}

		// -----------------------------------------------
    	if (!paused) {
			// calcula o tempo do quadro
			_frameTime = FrameTime();

			// atualização da aplicação 
			game->Update(_frameTime);

			if (onGraphics) {
				// limpa a tela para o próximo quadro
				graphics->Clear();

				// desenho da aplicação
				game->Draw();

				// renderiza sprites
				//renderer->Render();

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
			//renderer->Render();

			// apresenta o jogo na tela (troca backbuffer/frontbuffer)
			graphics->Present();
		}
	};

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
	_frameTime = CheckFrameSync();

#ifdef _DEBUG
	static string oldTitle = window->Title().c_str();
	// ----- START DEBUG ----------
	// tempo acumulado dos frames
	totalTime += _frameTime;

	// incrementa contador de frames
	frameCount++;

	// a cada 1000ms (1 segundo) atualiza indicador de FPS na janela
	if (totalTime >= 1.0f)
	{
		stringstream text;			// fluxo de texto para mensagens
		text << std::fixed;			// sempre mostra a parte fracionária
		text.precision(3);			// três casas depois da vírgula
		text << oldTitle << "   "
			<< "FPS: " << frameCount << "    "
			<< "Frame Time: " << _frameTime*1000 << " (ms)";

		SetWindowText(window->Id(), text.str().c_str());
		_context->window()->SetTitle(text.str());

		frameCount = 0;
		totalTime -= 1.0f;
	}
	// ------ END DEBUG -----------
#endif

	return _frameTime;
}

double _busyWait(double frameRateConstant, Timer& timer) {
	double frameTime = 1.0 / frameRateConstant;
	double timeNow = timer.ElapsedInSeconds();//ms
	double timeToSync = frameTime - timeNow;

	if (timeToSync > 0.002) { // Se o tempo restante for maior que 2ms, use Sleep
		std::this_thread::sleep_for(std::chrono::seconds(int(timeToSync)));
	}
	// Agora use um loop de espera ativa para o tempo restante
	while (timer.ElapsedInSeconds() < frameTime) {
		// Espera ativa
	}

	return frameTime;
}

double Engine::CheckFrameSync() {
	if (_frameRateType == CONSTANT) {
		return _busyWait(_frameRateConstant, timer);
	}
	else {
		return _busyWait(300, timer);//or timer.Reset()
	}
}




void Engine::SetFrameRateType(EngineFrameRateType type) {
	_context->graphics()->VSync(type == VSYNC);
	_frameRateType = type;
}

void Engine::SetFrameRate(ushort value) {
	_frameRateConstant = value;
	_frameRate = 1000 / _frameRateConstant;

}
int Engine::frameRate() const{
	return _frameRateType == CONSTANT ? _frameRateConstant : 1 / _frameTime;
}


// -------------------------------------------------------------------------------

//LRESULT CALLBACK Engine::EngineProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	// janela precisa ser repintada
//	if (msg == WM_PAINT) {
//	}
//	return CallWindowProc(DXInput::InputKeysProc, hWnd, msg, wParam, lParam);
//}

// -----------------------------------------------------------------------------
