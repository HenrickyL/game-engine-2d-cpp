#include "GLCamera.h"
#include <cmath>
#include "Shape3d.h"
#include "GLRenderer3D.h"

GLCamera::GLCamera(const Window* window) : Camera(window){
	Reset();
}

GLCamera::GLCamera(const Window* window, const Position& pos): Camera(window, pos) {
	Reset();
}


void GLCamera::UpdateFrustum() {
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov()), aspect(), zNear(), zFar());
	glm::mat4 viewMatrix = glm::lookAt(
		glm::vec3(position().x(), position().y(), position().z()),
		glm::vec3(_pointOfView.x(), _pointOfView.y(), _pointOfView.z()),
		glm::vec3(_orientation.x(), _orientation.y(), _orientation.z())
	);

	_frustum.Update(*this);
	//_frustum.Update(projectionMatrix, viewMatrix);
}

void GLCamera::UpdateProjection()const {
	// Configura a matriz de projeção
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//// Ajusta a matriz de projeção para manter a proporção da cena
	//gluPerspective(frustumFov(), _window->aspect(), _window->zNear(), _window->zFar());
	//glMatrixMode(GL_MODELVIEW);
}


void GLCamera::Update() {
	Position pos = position();
	_pointOfView = (pos + _direction);
	UpdateFrustum();
	gluLookAt(
		pos.x(), pos.y(), pos.z(),
		_pointOfView.x(), _pointOfView.y(), _pointOfView.z(),
		_orientation.x(), _orientation.y(), _orientation.z());
}


void GLCamera::LookAt(const Vector& pos) {
	//_direction.TranslateTo(pos);
	//_left.TranslateTo(pos);

}


void GLCamera::CalculeDirection() {
	this->rotations();
	//Vector adjust = Vector(rotations().y(), rotations().x(), rotations().z());
	// Criação do vetor de ajuste para os ângulos de rotação
	Vector adjust = Vector(
		fmod(rotations().x(), 360.0f),
		fmod(rotations().y(), 360.0f),
		fmod(rotations().z(), 360.0f)
	);
	// Normalização dos ângulos negativos para o intervalo de 0 a 360 graus
	if (adjust.x() < 0) adjust.SetX(adjust.x() + 360.0f);
	if (adjust.y() < 0) adjust.SetY(adjust.y() + 360.0f);
	if (adjust.z() < 0) adjust.SetZ(adjust.z() + 360.0f);

	// Conversão dos ângulos de rotação de graus para radianos
	float yaw = adjust.y() * M_PI / 180.0f;   // Rotação em torno do eixo Y
	float pitch = adjust.x() * M_PI / 180.0f; // Rotação em torno do eixo X
	float roll = adjust.z() * M_PI / 180.0f;  // Rotação em torno do eixo Z

	// Cálculo dos componentes da direção da câmera após rotação
	_direction.SetX(cos(pitch) * cos(yaw));
	_direction.SetY(sin(pitch));
	_direction.SetZ(cos(pitch) * sin(yaw));
	/*_direction.TranslateTo(Vector(cos(pitch) * cos(yaw),
		sin(pitch),
		cos(pitch) * sin(yaw)));*/

	// Aplicar rotação em torno do eixo Z (roll)
	float tempX = _direction.x() * cos(roll) - _direction.y() * sin(roll);
	float tempY = _direction.x() * sin(roll) + _direction.y() * cos(roll);

	_direction.SetX(tempX);
	_direction.SetY(tempY);

	// Normalização da direção da câmera para garantir um vetor unitário
	_direction = _direction.Unitary();

	_left = _orientation.CrossProduct(_direction).Unitary();
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
	Position _pointOfView = Position::Zero;
	Vector _orientation = Vector::Up;
	_direction = Vector::Zero;
	_left = Vector::Left;
	SetRotation(Vector::Up * -90);
	this->CalculeDirection();
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


void GLCamera::TranslateUp(float speed) {
	Movable::TranslateTo(_orientation * speed);
}
void GLCamera::TranslateDown(float speed) {
	Movable::TranslateTo(_orientation * -speed);
}

void GLCamera::MoveTo(const Position& pos) { Movable::MoveTo(pos); }



void GLCamera::Draw() {
	float _stroke = 2.5f;
	Color _axisX = Color::MAGENTA;
	Color _axisY = Color::WHITE;
	Color _axisZ = Color::GRAY;
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
	DrawFrustum();
}


bool GLCamera::IsInFrustum(const Position& position, float radius) const {
	return _frustum.IsInFrustum(glm::vec3(position.x(), position.y(), position.z()), radius);
}


//
//void GLCamera::DrawFrustum() {
//	Color color = Color::YELLOW;
//	Position pos = position();// _pointOfView;
//	glm::vec3 cameraPos = glm::vec3(pos.x(), pos.y(), pos.z());
//
//	// Calcula os vértices da base do frustum (near plane)
//	float halfHeight = tan(glm::radians(frustumFov() / 2.0f)) * frustumNear();
//	float halfWidth = halfHeight * frustumAspect();
//	glm::vec3 dir = glm::vec3(_direction.x(), _direction.y(), _direction.z());
//	glm::vec3 ori = glm::vec3(_orientation.x(), _orientation.y(), _orientation.z());
//	glm::vec3 left = glm::vec3(_left.x(), _left.y(), _left.z());
//
//
//	glm::vec3 centerNear = cameraPos + dir * frustumNear();
//	glm::vec3 topLeftNear = centerNear + (ori * halfHeight) - (left * halfWidth);
//	glm::vec3 topRightNear = centerNear + (ori * halfHeight) + (left * halfWidth);
//	glm::vec3 bottomLeftNear = centerNear - (ori * halfHeight) - (left * halfWidth);
//	glm::vec3 bottomRightNear = centerNear - (ori * halfHeight) + (left * halfWidth);
//
//	// Calcula os vértices da base do frustum (far plane)
//	float halfHeightFar = tan(glm::radians(frustumFov() / 2.0f)) * frustumFar();
//	float halfWidthFar = halfHeightFar * frustumAspect();
//	glm::vec3 centerFar = cameraPos + dir * frustumFar();
//	glm::vec3 topLeftFar = centerFar + (ori * halfHeightFar) - (left * halfWidthFar);
//	glm::vec3 topRightFar = centerFar + (ori * halfHeightFar) + (left * halfWidthFar);
//	glm::vec3 bottomLeftFar = centerFar - (ori * halfHeightFar) - (left * halfWidthFar);
//	glm::vec3 bottomRightFar = centerFar - (ori * halfHeightFar) + (left * halfWidthFar);
//
//	// Desenha as linhas da pirâmide truncada
//	glBegin(GL_LINES);
//		// Linhas do near plane
//		glVertex3fv(glm::value_ptr(topLeftNear));
//		glVertex3fv(glm::value_ptr(topRightNear));
//		glVertex3fv(glm::value_ptr(topRightNear));
//		glVertex3fv(glm::value_ptr(bottomRightNear));
//		glVertex3fv(glm::value_ptr(bottomRightNear));
//		glVertex3fv(glm::value_ptr(bottomLeftNear));
//		glVertex3fv(glm::value_ptr(bottomLeftNear));
//		glVertex3fv(glm::value_ptr(topLeftNear));
//
//		// Linhas do far plane
//		glVertex3fv(glm::value_ptr(topLeftFar));
//		glVertex3fv(glm::value_ptr(topRightFar));
//		glVertex3fv(glm::value_ptr(topRightFar));
//		glVertex3fv(glm::value_ptr(bottomRightFar));
//		glVertex3fv(glm::value_ptr(bottomRightFar));
//		glVertex3fv(glm::value_ptr(bottomLeftFar));
//		glVertex3fv(glm::value_ptr(bottomLeftFar));
//		glVertex3fv(glm::value_ptr(topLeftFar));
//
//		// Linhas conectando os planos
//		glVertex3fv(glm::value_ptr(topLeftNear));
//		glVertex3fv(glm::value_ptr(topLeftFar));
//		glVertex3fv(glm::value_ptr(topRightNear));
//		glVertex3fv(glm::value_ptr(topRightFar));
//		glVertex3fv(glm::value_ptr(bottomLeftNear));
//		glVertex3fv(glm::value_ptr(bottomLeftFar));
//		glVertex3fv(glm::value_ptr(bottomRightNear));
//		glVertex3fv(glm::value_ptr(bottomRightFar));
//	glEnd();
//}

void GLCamera::DrawFrustum() {
	const glm::vec3* nearVerts = _frustum.nearPlaneVertices();
	const glm::vec3* farVerts = _frustum.farPlaneVertices();

	/*glm::vec3 nearVerts[4] = {
		_nearVerts[0],
		_nearVerts[1],
		_nearVerts[3],
		_nearVerts[2]
	};

	glm::vec3 farVerts[4] = {
		_farVerts[0],
		_farVerts[1],
		_farVerts[3],
		_farVerts[2],
	};*/

	// Desenha as linhas da pirâmide truncada
	glBegin(GL_LINES);
	glColor3fv(Color::RED.c4f()); // Amarelo
	// Linhas do plano far
	for (int i = 0; i < 4; ++i) {
		glVertex3fv(glm::value_ptr(farVerts[i]));
		glVertex3fv(glm::value_ptr(farVerts[(i + 1) % 4]));
	}
	glColor3fv(Color::YELLOW.c4f()); // Amarelo
	// Linhas do plano near
	for (int i = 0; i < 4; ++i) {
		glVertex3fv(glm::value_ptr(nearVerts[i]));
		glVertex3fv(glm::value_ptr(nearVerts[(i + 1) % 4]));
	}
	glColor3fv(Color::YELLOW.c4f()); // Amarelo
	// Linhas conectando os planos near e far
	for (int i = 0; i < 4; ++i) {
		glVertex3fv(glm::value_ptr(nearVerts[i]));
		glVertex3fv(glm::value_ptr(farVerts[i]));
	}

	glEnd();
}