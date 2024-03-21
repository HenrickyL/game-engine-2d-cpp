#include "Input.h"

// -------------------------------------------------------------------------------
// inicialização de membros estáticos da classe
bool		Input::keys[256] = { 0 };						// estado do teclado/mouse
bool		Input::ctrl[256] = { 0 };						// controle de liberação das teclas
string		Input::text; 									// guarda caracteres digitados
short		Input::mouseWheel = 0;							// valor da roda do mouse
short		Input::lastMouseWheel = 0;
short		Input::dragOffset = 5;
Position	Input::mousePosition;
Position	Input::mouseClick;
Position	Input::lastMouseClick;
bool		Input::onClick = false;
Vector		Input::drag = Vector::Zero;

//TimeType	Input::lastTime = std::chrono::steady_clock::now();
short		Input::timeOffset = 600;


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

bool Input::KeyPress(InputKeys vkcode) {
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
	return mouseWheel;
}

short Input::MouseWheelDirection() {
	if (mouseWheel == 0) return 0;
	return mouseWheel > 0 ? 1 : -1;
}

bool Input::OnWheel() {
	return lastMouseWheel != mouseWheel;
}


// -------------------------------------------------------------------------------


// retorna verdadeiro se a tecla está pressionada
 bool Input::KeyDown(InputKeys vkcode)
{
	return Input::keys[vkcode];
}

// retorna verdadeiro se a tecla está liberada
 bool Input::KeyUp(InputKeys vkcode)
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
{return mousePosition.y();}

 Position Input::MousePosition() 
 { return Input::mousePosition; }

 Position Input::MouseClick() {
	 return Input::mouseClick;
 }

// retorna conteúdo do texto lido
 const char* Input::Text()
{return text.c_str();}


 bool  Input::OnClick() {
	 return onClick;
}

bool Input::OnDrag() {
	return drag.x() > dragOffset || drag.y() > dragOffset;
}

Vector Input::Drag() {
	return drag;
}
