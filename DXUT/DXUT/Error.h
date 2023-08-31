#ifndef DXUT_ERROR_H
#define DXUT_ERROR_H

#include <windows.h>
#include <string>
#include <map>
#include "TypeErrors.h"
using std::string;
using std::map;
// ---------------------------------------------------------------------------------
struct ErrorMessage {
	HRESULT code;
	const char* message;
};
// ---------------------------------------------------------------------------------

class Error {
private:
	HRESULT hres_code;
	string func_name;
	string file_name;
	int line_num;
	string error_message;
public:
	Error();
	Error(HRESULT hr, const string& func, const string& file, int line);
	string ToString() const;
};
// ---------------------------------------------------------------------------------

// Mapeamento de códigos de erro a mensagens
const map<HRESULT, const char*> errorMessages = {
	{ E_FAIL, "Erro geral" },
	{ E_INVALIDARG, "Argumento inválido" },
	{E_WINDOWCREATEFAILED, "Window creation failed"},
	{E_REGISTERWINDOWCLASSFAILED, "Register Window Failed"}
	// Adicione mais códigos e mensagens conforme necessário
};
// ---------------------------------------------------------------------------------
#ifndef ThrowIfFailed
#define ThrowIfFailed(x)                                               \
{                                                                      \
    HRESULT hr = (x);                                                  \
    if(FAILED(hr)) { throw Error(hr, __func__, __FILE__, __LINE__); }  \
}
#endif
// ---------------------------------------------------------------------------------

#endif

