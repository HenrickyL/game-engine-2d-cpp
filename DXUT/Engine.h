#ifndef DXUT_ENGINE_H
#define DXUT_ENGINE_H

#include "Graphics.h"					// dispositivo gráfico
#include "Window.h"						// janela da aplicação
#include "Input.h"						// dispositivo de entrada
#include "Timer.h"						// medidor de tempo
#include "Game.h"						// aplicação gráfica
#include "Renderer.h"                    // renderizador de sprites
#include "GraphicContext.h"
// ---------------------------------------------------------------------------------

enum EngineGraphicsType {
	E_DirectX,
	E_OpenGL
};

class Engine{ //singleton
private:
	static Timer timer;                 // medidor de tempo
	static bool paused;                 // estado do aplicação
	static bool onGraphics;                 // Desabilitar Graphics
	static Engine* instance;


	GraphicContext* _context;
	GraphicContext* _contextGL = nullptr;
	GraphicContext* _contextDX = nullptr;
	EngineGraphicsType _graphicType = E_OpenGL;
	GraphicType _type = T_2D;
	float FrameTime();					// calcula o tempo do quadro
	int Loop();							// laço principal do motor

	Engine();							// construtor

	GraphicContext* getContextByType(EngineGraphicsType type);


public:
	static Game		* game;					// aplicação a ser executada
	static Window	* window;				// janela da aplicação
	//static Renderer	* renderer;          // renderizador de sprites
	static float	  frameTime;			// tempo do quadro atual

	static Engine* Instance();
	~Engine();							// destrutor

	void DisableGraphics();
	void EnableGraphics();
	//fps
	void SetGraphicsFPS(FPSType fps);
	FPSType GraphicsFPS() const;
	
	EngineGraphicsType graphicType() const;
	GraphicType engineType() const;

	void SetGraphicType(EngineGraphicsType value);
	void SetType(GraphicType value);

	GraphicContext* context();



	int Start(Game* level);		// inicia o execução da aplicação

	static void Pause();                // pausa o motor
	static void Resume();               // reinicia o motor

	// trata eventos do Windows
	static LRESULT CALLBACK EngineProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

//inline functions
inline void Engine::Pause()
{paused = true; timer.Stop(); game->OnPause();}
inline void Engine::Resume()
{	paused = false; timer.Start(); game->OnResume();}
inline void Engine::DisableGraphics()
{	onGraphics = false;}
inline void Engine::EnableGraphics()
{	onGraphics = true;}

inline EngineGraphicsType Engine::graphicType() const{ return this->_graphicType; }
inline GraphicType Engine::engineType() const { return _context->graphics()->type(); }


inline void Engine::SetType(GraphicType value) { _context->graphics()->SetType(value); }

//fps
inline void Engine::SetGraphicsFPS(FPSType fps) 
{_context->graphics()->SetFPS(fps);}

inline FPSType Engine::GraphicsFPS() const 
{return _context->graphics()->FPS();}

#endif