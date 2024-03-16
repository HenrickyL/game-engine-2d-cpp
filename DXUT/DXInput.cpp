#include "DXInput.h"
#include "DXKeyMap.h"
DXProcType DXInput::winProcPtr = DXWindow::WinProc;

//void DXInput::Read() {
//	// apaga texto armazenado
//	text.clear();
//	// altera a window procedure da janela ativa
//	SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)DXInput::Reader);
//}


InputKeys DXInput::GetKey(WPARAM key) {
	return DXKeyMap[key];
}


LRESULT CALLBACK DXInput::Reader(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// processa teclas de caracteres
	case WM_CHAR:
		switch (wParam)
		{
			// Backspace
		case 0x08:
			if (!text.empty())
				text.erase(text.size() - 1);
			break;

			// Tab e Enter
		case 0x09:
		case 0x0D:
			// altera a window procedure da janela ativa
			SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)DXInput::InputKeysProc);
			break;

			// Caracteres
		default:
			text += char(wParam);
			break;
		}
		// ATENÇÃO: não será necessário quando estiver operando com DirectX
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	}

	return CallWindowProc(DXInput::InputKeysProc, hWnd, msg, wParam, lParam);
}
// -------------------------------------------------------------------------------
LRESULT CALLBACK DXInput::InputKeysProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	InputKeys keyCode = GetKey(wParam);

	switch (msg)
	{
		// tecla pressionada
	case WM_KEYDOWN:
		keys[keyCode] = true;
		return 0;

		// tecla liberada
	case WM_KEYUP:
		keys[keyCode] = false;
		return 0;

		// movimento do mouse
	case WM_MOUSEMOVE:
		mousePosition.SetX((int)GET_X_LPARAM(lParam));
		mousePosition.SetY((int)GET_Y_LPARAM(lParam));
		return 0;

		// movimento da roda do mouse
	case WM_MOUSEWHEEL:
		mouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
		return 0;

		// botão esquerdo do mouse pressionado
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		keys[GetKey(VK_LBUTTON)] = true;
		return 0;

		// botão do meio do mouse pressionado
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
		keys[GetKey(VK_MBUTTON)] = true;
		return 0;

		// botão direito do mouse pressionado
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		keys[GetKey(VK_RBUTTON)] = true;
		return 0;

		// botão esquerdo do mouse liberado
	case WM_LBUTTONUP:
		keys[GetKey(VK_LBUTTON)] = false;
		return 0;

		// botão do meio do mouse liberado
	case WM_MBUTTONUP:
		keys[GetKey(VK_MBUTTON)] = false;
		return 0;

		// botão direito do mouse liberado
	case WM_RBUTTONUP:
		keys[GetKey(VK_RBUTTON)] = false;
		return 0;
		//desabilitar Alt+f4
		/*case WM_SYSKEYDOWN:
			if (wParam == VK_F4) {
				return 0;
			}
			break;*/
	}


	return CallWindowProc(DXInput::winProcPtr, hWnd, msg, wParam, lParam);
}