#ifndef DXUT_ENGINE_H
#define DXUT_ENGINE_H

#include "Graphics.h"					// dispositivo gr�fico
#include "Window.h"						// janela da aplica��o
#include "Input.h"						// dispositivo de entrada
#include "Timer.h"						// medidor de tempo
#include "Game.h"						// aplica��o gr�fica

// ---------------------------------------------------------------------------------

class Engine{
private:
	static Graphics* graphics;          // dispositivo gr�fico
	static Timer timer;					// medidor de tempo
	static bool paused;                 // estado do aplica��o
	static bool onGraphics;                 // Desabilitar Graphics
	static Engine* instance;


	float FrameTime();					// calcula o tempo do quadro
	int Loop();							// la�o principal do motor

	Engine();							// construtor

public:
	static Game		* app;					// aplica��o a ser executada
	static Window	* window;				// janela da aplica��o
	static Input	* input;				// dispositivos de entrada da aplica��o
	static float	  frameTime;			// tempo do quadro atual

	static Engine* Instance();
	~Engine();							// destrutor

	void DisableGraphics();
	void EnableGraphics();
	Engine* & GetInstance();


	int Start(Game* level);		// inicia o execu��o da aplica��o

	static void Pause();                // pausa o motor
	static void Resume();               // reinicia o motor

	// trata eventos do Windows
	static LRESULT CALLBACK EngineProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

//inline functions
inline void Engine::Pause()
{	paused = true; timer.Stop(); app->OnPause();}

inline void Engine::Resume()
{	paused = false; timer.Start(); app->OnResume();}
inline void Engine::DisableGraphics()
{	onGraphics = false;}
inline void Engine::EnableGraphics()
{	onGraphics = true;}
#endif