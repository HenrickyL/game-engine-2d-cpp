#ifndef DXUT_TIMER_H
#define DXUT_TIMER_H

#include <windows.h>			// acesso ao contador de alta precisão do Windows

class Timer //Singleton
{
private:
	LARGE_INTEGER start, end;	// valores de início e fim do contador
	LARGE_INTEGER freq;			// frequência do contador
	bool stoped = true;				// estado da contagem


public:
	Timer();					// construtor

	void  Start();				// inicia/retoma contagem do tempo
	void  Stop();				// para contagem do tempo
	double Reset();				// reinicia contagem e retorna tempo transcorrido
	double ElapsedInSeconds();			// retorna tempo transcorrido em segundos	
	double Elapsed();			// retorna tempo transcorrido em ms

	bool  ElapsedSec(double secs);	// verifica se transcorreu "secs" segundos
	bool  Elapsed(double ms);	// verifica se transcorreu "secs" segundos
	bool  isStop() const;
};
// -------------------------------------------------------------------------------

// Funções Inline

inline bool Timer::ElapsedSec(double secs)
{
	return ElapsedInSeconds() >= secs;
}

inline bool Timer::Elapsed(double ms)
{
	return Elapsed() >= ms;
}


inline bool Timer::isStop() const {
	return stoped;
}

// -

#endif