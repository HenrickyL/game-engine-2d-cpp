#ifndef DXUT_INPUT_H
#define DXUT_INPUT_H

#include "InputKeys.h"
#include "Position.h"
#include <string>
using std::string;

class Input {
protected:
	static bool	keys[256];				// estado das teclas do teclado/mouse
	static bool ctrl[256];				// controle da liberação de teclas
	static string text;					// armazenamento para os caracteres digitados

	static Position		mousePosition;
	static Position		mouseClick;
	static short		mouseWheel;		// valor da roda do mouse
public:
	//Input();							// construtor
	//~Input();							// destrutor

	static bool KeyDown(int vkcode);		    // retorna se tecla está pressionada
	static bool KeyUp(int vkcode);			    // retorna se tecla está liberada
	static bool KeyPress(int vkcode);		    // novo pressionamento somente após liberação		

	static int   MouseX();						// retorna posição x do mouse
	static int   MouseY();						// retorna posição y do mouse
	static Position MousePosition();

	static short MouseWheel();					// retorna rotação da roda do mouse

	static void  Read();						// armazena texto digitado até o próximo ENTER ou TAB
	static const char* Text();			// retorna endereço do texto armazenada
};

#endif