#ifndef DXUT_DXINPUT_H
#define DXUT_DXINPUT_H

#include "Input.h"
#include "DXWindow.h"

typedef LRESULT(*DXProcType)(HWND, UINT, WPARAM, LPARAM);

class DXInput : public Input {
public:
	static DXProcType winProcPtr;

	// trata eventos do Windows
	static LRESULT CALLBACK Reader(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK InputKeysProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void  Read() override;
};
#endif