#include "StatePosition.h"
//------------------------------------------
#include "Engine.h"
#include "Transition.h"
#include "MovimentAction.h"
#include "Action.h"
#include "Dictionary.h"
//------------------------------------------

Window*& StatePosition::window = Engine::window;


StatePosition::StatePosition(const Position& pos) {
	int x = pos.X();
	int y = pos.Y();
	name = "(x: " + std::to_string(x) + ", y: " + std::to_string(y) + ")";
	_position = new Position(x, y);
	value = *_position;
}

StatePosition::~StatePosition() {
	if (_position) delete _position;
	if (_sprite) delete _sprite;
	if (_bbox) delete _bbox;
	DeleteEdges();
}


//void StatePosition::Generate(const vector<Action<Position>*> actions, Dictionary<Position>* controlGenerated){
//	for (auto* action : actions) {
//		StatePosition* currentGenerated = dynamic_cast<StatePosition*>(action->Generate(this));
//		Position currentPosition = currentGenerated->GetPosition();
//		if (controlGenerated) {
//			if (currentGenerated && !this->ExistInEdge(currentGenerated) && !controlGenerated->Contains(currentPosition)) {
//				AddTransition(new Transition<Position>(this, currentGenerated, action));
//				controlGenerated->Add(currentPosition, currentGenerated);
//			}
//			else {
//				delete currentGenerated; // Descarte o estado ambíguo
//			}
//		}
//		else {
//			// Verifique se o novo estado já existe na lista de estados ou se é ambíguo
//			if (currentGenerated && !this->ExistInEdge(currentGenerated)) {
//				AddTransition(new Transition<Position>(this, currentGenerated, action));
//			}
//			else {
//				delete currentGenerated; // Descarte o estado ambíguo
//			}
//		}
//	}
//}

float StatePosition::GetHeuristic(State<Position>* _target) const {
	StatePosition* target = dynamic_cast<StatePosition*>(_target);
	if (target) {
		Position p = target->GetPosition();
		return this->GetPosition().Distance(p);
	}
	return 0.0f;
}


void StatePosition::Update() {

}

bool StatePosition::Equal(State<Position>* _other) const {
	StatePosition* other = dynamic_cast<StatePosition*>(_other);
	if (other) {
		return this->GetPosition() == other->GetPosition() || this == _other;
	}
	return false;
}


bool StatePosition::IsGeneratedPossible() const {
	return true;
}


