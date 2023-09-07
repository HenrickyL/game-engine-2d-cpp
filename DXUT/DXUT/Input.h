#ifndef DXUT_INPUT_H
#define DXUT_INPUT_H

#include "Window.h"
#include "InputKeys.h"

class Input {
private:
	static bool	keys[256];				// estado das teclas do teclado/mouse
	static bool ctrl[256];				// controle da liberação de teclas
	static string text;					// armazenamento para os caracteres digitados

	static Point*	mousePosition;
	static short	mouseWheel;			// valor da roda do mouse
public:
	Input();							// construtor
	~Input();							// destrutor

	bool KeyDown(int vkcode);		    // retorna se tecla está pressionada
	bool KeyUp(int vkcode);			    // retorna se tecla está liberada
	bool KeyPress(int vkcode);		    // novo pressionamento somente após liberação		

	int   MouseX() const;						// retorna posição x do mouse
	int   MouseY() const;						// retorna posição y do mouse
	Point MousePosition() const;

	short MouseWheel();					// retorna rotação da roda do mouse

	void  Read();						// armazena texto digitado até o próximo ENTER ou TAB
	static const char* Text();			// retorna endereço do texto armazenada

	// trata eventos do Windows
	static LRESULT CALLBACK Reader(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK InputProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
// ---------------------------------------------------------------------------------
// Inline Member Functions

// retorna verdadeiro se a tecla está pressionada
inline bool Input::KeyDown(int vkcode)
{	return keys[vkcode];}

// retorna verdadeiro se a tecla está liberada
inline bool Input::KeyUp(int vkcode)
{	return !(keys[vkcode]);}

// retorna a posição do mouse no eixo x
inline int Input::MouseX() const
{	return mousePosition->X();}

// retorna a posição do mouse no eixo y
inline int Input::MouseY() const
{	return mousePosition->Y();}
inline Point Input::MousePosition() const { return Point(Input::mousePosition); }

// retorna conteúdo do texto lido
inline const char* Input::Text()
{	return text.c_str();}


#endif