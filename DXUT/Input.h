#ifndef DXUT_INPUT_H
#define DXUT_INPUT_H

#include "InputKeys.h"
#include "Position.h"
#include "Vector.h"
#include <string>
//#include <chrono>
using std::string;


//using TimeType = std::chrono::steady_clock::time_point;


class Input {
protected:
	static bool	keys[256];				// estado das teclas do teclado/mouse
	static bool ctrl[256];				// controle da liberação de teclas
	static string text;					// armazenamento para os caracteres digitados

	static Position		mousePosition;
	static Position		mouseClick;
	static Position		lastMouseClick;
	static Vector		drag;
	static short		dragOffset;
	static short		mouseWheel;		// valor da roda do mouse
	static short		lastMouseWheel;
	static bool			onClick;
	//static TimeType		lastTime;
	static short		timeOffset;


public:
	//Input();							// construtor
	//~Input();							// destrutor

	static bool KeyDown(InputKeys vkcode);		    // retorna se tecla está pressionada
	static bool KeyUp(InputKeys vkcode);			    // retorna se tecla está liberada
	static bool KeyPress(InputKeys vkcode);		    // novo pressionamento somente após liberação		

	static int   MouseX();						// retorna posição x do mouse
	static int   MouseY();						// retorna posição y do mouse
	static Position MousePosition();
	static Position MouseClick();
	static bool OnDrag();
	static Vector Drag();


	static bool OnClick();

	static short MouseWheel();					// retorna rotação da roda do mouse
	static short MouseWheelDirection();	
	static bool OnWheel();


	static void  Read();						// armazena texto digitado até o próximo ENTER ou TAB
	static const char* Text();			// retorna endereço do texto armazenada
};

#endif