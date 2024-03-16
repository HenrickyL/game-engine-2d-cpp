#include "Input.h"

// -------------------------------------------------------------------------------
// inicialização de membros estáticos da classe

bool		Input::keys[256] = { 0 };						// estado do teclado/mouse
bool		Input::ctrl[256] = { 0 };						// controle de liberação das teclas
string		Input::text; 									// guarda caracteres digitados
short		Input::mouseWheel = 0;							// valor da roda do mouse
Position	Input::mousePosition;
Position	Input::mouseClick;

// -------------------------------------------------------------------------------

//Input::Input()
//{
//	// ATENÇÂO: supõe que a janela já foi criada com uma chamada a window->Create();
//	// altera a window procedure da janela ativa para InputProc
//	//SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)Input::InputProc);
//}
//// -------------------------------------------------------------------------------
//
//Input::~Input()
//{
//	// volta a usar a Window Procedure da classe Window
//	//SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)Input::winProcPtr);
//}

// -------------------------------------------------------------------------------

bool Input::KeyPress(int vkcode) {
	if (ctrl[vkcode]) {
		if (KeyDown(vkcode)) {
			ctrl[vkcode] = false;
			return true;
		}
	}
	else if (KeyUp(vkcode)) {
		ctrl[vkcode] = true;
	}
	return false;
}
// -------------------------------------------------------------------------------

short Input::MouseWheel()
{
	short val = mouseWheel;
	mouseWheel = 0;
	return val;
}

// -------------------------------------------------------------------------------


// retorna verdadeiro se a tecla está pressionada
 bool Input::KeyDown(int vkcode)
{
	return Input::keys[vkcode];
}

// retorna verdadeiro se a tecla está liberada
 bool Input::KeyUp(int vkcode)
{
	return !(Input::keys[vkcode]);
}

// retorna a posição do mouse no eixo x
 int Input::MouseX()
{
	return Input::mousePosition.x();
}

// retorna a posição do mouse no eixo y
 int Input::MouseY()
{
	return mousePosition.y();
}
 Position Input::MousePosition() { return Input::mousePosition; }

// retorna conteúdo do texto lido
 const char* Input::Text()
{
	return text.c_str();
}

