#include "Input.h"

// -------------------------------------------------------------------------------
// inicialização de membros estáticos da classe

bool Input::keys[256] = { 0 };							// estado do teclado/mouse
bool Input::ctrl[256] = { 0 };							// controle de liberação das teclas
string Input::text; 									// guarda caracteres digitados
Position*	Input::mousePosition = nullptr;
short	Input::mouseWheel = 0;							// valor da roda do mouse
WinProcType Input::winProcPtr = DXWindow::WinProc;

// -------------------------------------------------------------------------------

Input::Input()
{
	mousePosition = new Position();
	// ATENÇÂO: supõe que a janela já foi criada com uma chamada a window->Create();
	// altera a window procedure da janela ativa para InputProc
	SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)Input::InputProc);
}
// -------------------------------------------------------------------------------

Input::~Input()
{
	delete mousePosition;
	// volta a usar a Window Procedure da classe Window
	SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)Input::winProcPtr);
}

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


// -------------------------------------------------------------------------------


// -------------------------------------------------------------------------------

