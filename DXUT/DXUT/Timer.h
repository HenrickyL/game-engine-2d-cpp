#ifndef DXUT_TIMER_H
#define DXUT_TIMER_H

#include <windows.h>			// acesso ao contador de alta precisão do Windows

class Timer //Singleton
{
private:
	LARGE_INTEGER start, end;	// valores de início e fim do contador
	LARGE_INTEGER freq;			// frequência do contador
	bool stoped;				// estado da contagem
	static Timer* instance;			// instance


	Timer();					// construtor

public:
	static Timer* Intance();
	~Timer();					// destrutor

	void  Start();				// inicia/retoma contagem do tempo
	void  Stop();				// para contagem do tempo
	float Reset();				// reinicia contagem e retorna tempo transcorrido
	float Elapsed();			// retorna tempo transcorrido em segundos	
	bool  Elapsed(float secs);	// verifica se transcorreu "secs" segundos
};
// -------------------------------------------------------------------------------

// Funções Inline

inline bool Timer::Elapsed(float secs)
{
	return (Elapsed() >= secs ? true : false);
}

// -

#endif