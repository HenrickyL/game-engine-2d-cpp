#include "UT_Utils.h"
#include <iostream>
#include <random>

// ---------------------------------------------------------------------------

float RandomUtils::GetRandomFloat(float min, float max) {
	std::random_device rd;  // Objeto para fornecer uma semente aleatória
	std::mt19937 gen(rd()); // Gerador de números aleatórios Mersenne Twister
	std::uniform_real_distribution<float> dis(min, max); // Distribuição uniforme de números reais
	return dis(gen);
}
int RandomUtils::GetRandomInt(int min, int max) {
	return static_cast<int>(
		RandomUtils::GetRandomFloat(static_cast<float>(min), static_cast<float>(max))
	);
}

// ---------------------------------------------------------------------------
