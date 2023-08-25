#ifndef DXUT_ENGINE_H
#define DXUT_ENGINE_H

#include "Graphics.h"					// dispositivo gráfico
#include "Window.h"						// janela da aplicação
#include "Input.h"						// dispositivo de entrada
#include "Timer.h"						// medidor de tempo
#include "App.h"						// aplicação gráfica

// ---------------------------------------------------------------------------------

class Engine{
private:
	static Graphics* graphics;          // dispositivo gráfico
	static Timer timer;					// medidor de tempo
	static bool paused;                 // estado do aplicação

	float FrameTime();					// calcula o tempo do quadro
	int Loop();							// laço principal do motor

public:
	static Window* window;				// janela da aplicação
	static Input* input;				// dispositivos de entrada da aplicação
	static App* app;					// aplicação a ser executada
	static float frameTime;				// tempo do quadro atual

	Engine();							// construtor
	~Engine();							// destrutor

	int Start(App* application);		// inicia o execução da aplicação

	static void Pause();                // pausa o motor
	static void Resume();               // reinicia o motor

	// trata eventos do Windows
	static LRESULT CALLBACK EngineProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

//inline functions
inline void Engine::Pause()
{	paused = true; timer.Stop();}

inline void Engine::Resume()
{ 	paused = false; timer.Start();}
#endif