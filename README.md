# 2D Game Engine cpp

* Engine

* Direct3D - Sprites

* Ai Module
  * Agent & Environment (To do)
  * [SearchMethods](https://github.com/HenrickyL/game-engine-2d-cpp/blob/17-ai-initial/DXUT/DXUT/SearchMethods.h) State-Transitions


Reference: [Programação de Jogos](https://www.youtube.com/watch?v=EuQyOyN6keA&list=PLX6Nyaq0ebfjfo4PlkAcKRxR66qXZk899) - [Prof. Judson Santiago](https://www.linkedin.com/in/judson-santiago-bb83661b2/)



--------------------

## Where to start?

Main: [WinMain.cpp](https://github.com/HenrickyL/game-engine-2d-cpp/blob/develop/DXUT/DXUT/WinMain.cpp)

```cpp
#include "DXUT.h"
#include "AiTest.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	  //...
		// engine->window->Mode(WINDOWED);
		// engine->window->Size(800, 600);
		// engine->window->Color(1, 1,0);
		// engine->window->Title("My Game");
		// engine->window->Icon(IDI_ICON);
		// engine->SetGraphicsFPS(FPS_MONITOR);
		// engine->window->LostFocus(Engine::Pause);
		// engine->window->InFocus(Engine::Resume);
		// cria e executa a aplicação
		int exitCode = engine->Start(new AiTest());
    //...
```

## Documentation

- [How to create your problem for A*](DXUT/DXUT/HowToCreateYourProblemAStar.md)

--------------------

## Some examples
###  Initial Sprite with Frog game
![](img/Frog.gif)

### Colision

#### Galaga

![](img/galaga-colision.gif)

#### Breakout





Reference: [Programação de Jogos](https://www.youtube.com/watch?v=EuQyOyN6keA&list=PLX6Nyaq0ebfjfo4PlkAcKRxR66qXZk899) - [Prof. Judson Santiago](https://www.linkedin.com/in/judson-santiago-bb83661b2/)
![](img/breakout-colision.gif)


### Physics

![](img/test-physic.gif)



