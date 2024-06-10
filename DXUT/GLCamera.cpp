#include "GLCamera.h"
#include <cmath>
GLCamera::GLCamera(const Window* window) : Camera(window) {}

GLCamera::GLCamera(const Window* window, const Position& pos): Camera(window, pos) {}


void GLCamera::Update() {
	_pointOfView = (position() + _direction);
	gluLookAt(
		position().x(), position().y(), position().z(),
		_pointOfView.x(), _pointOfView.y(), _pointOfView.z(),
		_orientation.x(), _orientation.y(), _orientation.z());
}


void GLCamera::LookAt(const Vector& pos) {
	//_direction.TranslateTo(pos);
	//_left.TranslateTo(pos);

}


void GLCamera::CalculeDirection() {
	Vector adjust = Vector(rotations().y(), rotations().x(), rotations().z());
	float yaw = adjust.y() * M_PI / 180.0f;   // Rotação em torno do eixo Y
	float pitch = adjust.x() * M_PI / 180.0f; // Rotação em torno do eixo X
	float roll = adjust.z() * M_PI / 180.0f; // Rotação em torno do eixo Z


	_direction.SetX(cos(pitch) * cos(yaw));
	_direction.SetY( sin(pitch));
	_direction.SetZ(cos(pitch) * sin(yaw));

	// Aplicar rotação em torno do eixo Z (roll)
	float tempX = _direction.x() * cos(roll) - _direction.y() * sin(roll);
	float tempY = _direction.x() * sin(roll) + _direction.y() * cos(roll);

	_direction.SetX(tempX);
	_direction.SetY(tempY);

	_direction = _direction.Unit();

	// Atualize os vetores _left e _up corretamente
	_left = _orientation.CrossProduct(_direction).Unit();
}


void GLCamera::RotateBy(const Vector& delta) {
	Movable::RotateBy(delta);
	this->CalculeDirection();
	
}

void GLCamera::TranslateTo(const Vector& delta) {}

void GLCamera::RotateTo(const Vector& delta) {
	Movable::RotateTo(delta);
	this->CalculeDirection();
}



void GLCamera::Reset() {
	Camera::Reset();
	_direction = Vector::Backward;
	_left = Vector::Left;
}



void GLCamera::TranslateLeft(float speed) {
	Movable::TranslateTo(_left * speed);
}
void GLCamera::TranslateRight(float speed){
	Movable::TranslateTo(_left * -speed);

}
void GLCamera::TranslateForward(float speed){
	Movable::TranslateTo(_direction * speed);
}
void GLCamera::TranslateBackward(float speed){
	Movable::TranslateTo(_direction * -speed);
}

void GLCamera::MoveTo(const Position& pos) { Movable::MoveTo(pos); }



void GLCamera::Draw() {
	float _stroke = 2.5f;
	Color _axisX = Color::MAGENTA;
	Color _axisY = Color::YELLOW;
	Color _axisZ = Color::WHITE;
	float _length = 1.0f;
	Position origin = position();
	//glEnable(GL_LINE_SMOOTH); //antialising
	glLineWidth(_stroke);
	glBegin(GL_LINES);
		// Eixo X (vermelho)
		glColor3fv(_axisX.c3f());
		glVertex3fv(origin.p3f());
		glVertex3fv((origin+_direction).p3f());
		// Eixo Y (verde)
		glColor3fv(_axisY.c3f());
		glVertex3fv(origin.p3f());
		glVertex3fv((origin + _orientation).p3f());
		// Eixo Z (azul)
		glColor3fv(_axisZ.c3f());
		glVertex3fv(origin.p3f());
		glVertex3fv((origin + _left).p3f());
	glEnd();
}