#include "MyGame.h"
#include "Engine.h" 
#include "UT_Utils.h"
#include <cmath>
#include <iostream>

void MyGame::Init() {
	window = Engine::window;
	_drawnner3D.SetFillMode(F_WIREFRAME_SOLID);
	_drawnner3D.InitializeShader();
	//Geometries

	//Shapes
	int qtd = 20;
	float dTheta = 360 / qtd;
	float theta = 0;
	float y = 1;
	Shape3D* s;
	float dist = RandomUtils::GetRandomFloat(0.5f, 16.0f);
	for (int i = 0; i < qtd; i++) {

		float x = dist*std::cos(theta);
		float z = dist * std::sin(theta);
		Position p = Position(x, y, z);
		Color color = Color::RandomColor();
		int value = RandomUtils::GetRandomInt(0, 100);
		float size = RandomUtils::GetRandomFloat(0.3f, 0.5f);


		if (value % 2 == 0) {
			s = new Cube(p, size, color);
		}
		else if (value % 3 == 0){
			s = new Plane(p, size, color);
		}
		else {
			s = new Sphere(p, size*0.6, color);
		}

		s->RotateBy(Vector(
			RandomUtils::GetRandomInt(0, 360),
			RandomUtils::GetRandomInt(0, 360),
			RandomUtils::GetRandomInt(0, 360)
		));


		shapes.push_back(s);
		theta += dTheta;
	}
	currentIndex = 0;
	current = shapes[currentIndex];
	current->SetColor(Color::YELLOW);

	currentCam = &cam;
	
	_drawnner3D.AddToDisplayList(&groundUi);
	_drawnner3D.AddToDisplayList(&wordOrigin);
}

void MyGame::Update(double dt){
	//frameTime = 0.1;
	static double frameTime = 0.01;
	static bool isDt = true;
	static bool isConstant = true;
	

	if (Input::KeyPress(KEY_R)) {
		Reset();
	}
	InputEnd();
	InputRotationGlobal();
	InputRotationLocal();
	InputCamera();
	if (Input::KeyPress(KEY_L)) {
		current->SetColor(Color::GREEN);
		currentIndex = (currentIndex + 1) % shapes.size();
		current = shapes[currentIndex];
		current->SetColor(Color::YELLOW);
	}

	if (Input::KeyPress(KEY_F)) {
		isConstant = !isConstant;
		Engine::Instance()->SetFrameRateType(isConstant ? CONSTANT : VARIABLE);
	}

	if (Input::KeyPress(KEY_T)) {
		onSolid = (onSolid + 1) % 4;
		_drawnner3D.SetFillMode((FillModeEnum)onSolid);
	}
	

	glLoadIdentity();
	currentCam->Update();


	glTranslatef(0, 0, 0);
	glRotatef(globalRotation.x(), 1, 0, 0);
	glRotatef(globalRotation.y(), 0, 1, 0);
	glRotatef(globalRotation.z(), 0, 0, 1);
}

void MyGame::Draw(){
	_drawnner3D.DrawDisplayList();
	for (Shape3D* s : shapes) {
		_drawnner3D.Draw(*s);
	}
	for (Geometry* g : geometries) {
		_drawnner.Draw(*g);
	}
	cam2.Draw();
	cam.Draw();
}

void MyGame::Finalize(){
	for (Shape3D* s : shapes) {
		delete s;
	}
	for (Geometry* g : geometries) {
		delete g;
	}
}

// ---------------------------------------------------------------------------


void MyGame::InputRotationGlobal() {
	float delta = 0.5;
	Vector dir = Vector::Zero;

	if ((Input::KeyDown(CTRL_LEFT) || Input::KeyDown(CTRL_RIGHT)) && Input::OnWheel()) {
		float step = 2;
		int orientation = Input::MouseWheelDirection();
		if (orientation != 0) {
			//Y
			if (Input::KeyDown(SHIFT_LEFT)) {
				dir = Vector::Up;
			}
			//Z
			else if (Input::KeyDown(SHIFT_RIGHT)) {
				dir = Vector::Forward;
			}//X
			else {
				dir = Vector::Right;
			}
			globalRotation.TranslateTo(dir * delta * orientation);

		}
	}
}

void MyGame::InputRotationLocal()
{
	if (current == nullptr) return;
	float delta = 3;
	Vector dir = Vector::Zero;

	if ( !(Input::KeyDown(CTRL_LEFT) || Input::KeyDown(CTRL_RIGHT)) && Input::OnWheel()) {
		float step = 2;
		int orientation =  Input::MouseWheelDirection();
		if (orientation != 0) {
			//Y
			if (Input::KeyDown(SHIFT_LEFT)) {
				dir = Vector::Up;
			}
			//Z
			else if (Input::KeyDown(SHIFT_RIGHT)) {
				dir = Vector::Forward;
			}//X
			else {
				dir = Vector::Right;
			}
			current->RotateBy(dir * delta * orientation);
		}
	}
	float speed = 0.001;
	if (Input::KeyDown(LEFT)) {
		current->TranslateTo(Vector::Left * speed);
	}
	else if (Input::KeyDown(RIGHT)) {
		current->TranslateTo(Vector::Right * speed);
	}


	if (!Input::KeyDown(SHIFT_LEFT)) {
		if (Input::KeyDown(UP)) {
			current->TranslateTo(Vector::Backward * speed);

		}
		else if (Input::KeyDown(DOWN)) {
			current->TranslateTo(Vector::Forward * speed);
		}
	}
	else {
		if (Input::KeyDown(UP)) {
			current->TranslateTo(Vector::Up * speed);

		}
		else if (Input::KeyDown(DOWN)) {
			current->TranslateTo(Vector::Down * speed);
		}
	}
	
}

void MyGame::InputCamera()
{
	float delta = 0.005;
	if (Input::KeyDown(SHIFT_LEFT)) {
		delta = 0.02;
		
	}
	else {
		delta = 0.005;
		
	}

	if (Input::KeyDown(CTRL_LEFT)) {
		if (Input::KeyDown(KEY_W)) {
			//cam.TranslateTo(Vector::Up * delta);
		}
		else if (Input::KeyDown(KEY_S)) {
			//cam.TranslateTo(Vector::Down * delta);
		}
	}
	else {
		if (Input::KeyDown(KEY_W)) {
			currentCam->TranslateForward(delta);

		}
		else if (Input::KeyDown(KEY_S)) {
			currentCam->TranslateBackward(delta);
		}
	}
	

	if (Input::KeyDown(KEY_A)) {
		currentCam->TranslateLeft(delta);

	}
	else if (Input::KeyDown(KEY_D)) {
		currentCam->TranslateRight(delta);
	}
	
	
	float value = 0.05;
	Vector v =Input::MousePositionOffset();
	
	if (v.x() != 0 || v.y() != 0) {
		v = Vector(v.y(), v.x()) * Vector( 1,1)* value;
		currentCam->RotateBy(v);
	}

	float rotSpeed = delta*10;

	v =Vector(0,1);
	if (Input::KeyDown(KEY_Q)) {
		v = (v * -rotSpeed);
		currentCam->RotateBy(v);
	}else if(Input::KeyDown(KEY_E)){
		v = (v * rotSpeed);
		currentCam->RotateBy(v);
	}

	if (Input::KeyPress(KEY_P)) {
		if (currentCam == &cam) {
			currentCam = &cam2;
		}
		else {
			currentCam = &cam;
		}
	}



}

void MyGame::Reset()
{
	globalRotation = Vector::Zero;
	cam.MoveTo(Position(0, 0.5f, 4));
	cam2.MoveTo(Position(0,1.0f, 3));
	currentCam->Reset();
}


void MyGame::InputEnd() {
	if (Input::KeyPress(ESCAPE)) {
		window->Close();
	}
}
