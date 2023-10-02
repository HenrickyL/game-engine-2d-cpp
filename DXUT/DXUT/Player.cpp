#include "Player.h"
// ------------------------
#include "StatePosition.h"
#include "SearchMethods.h"
// ------------------------

Player::Player(Image* img, const Position& p) {
	_position = new Position();
	this->SetSprite(new Sprite(img));
	_magnitude= 100;
	_sprite->SetLayer(Layer::MIDDLE);
    _sprite->SetScale(0.01f);
	BBox(_sprite->GetCircle());

    Action* up = new MovimentAction(Vector::Up);
    Action* down = new MovimentAction(Vector::Down);
    Action* left = new MovimentAction(Vector::Left);
    Action* right = new MovimentAction(Vector::Right);

    actions.push_back(up);
    actions.push_back(down);
    actions.push_back(left);
    actions.push_back(right);
    initial = p;

}

Player::~Player() {
    for (Action* a : actions) {
        delete a;
    }
}



void Player::Update() {
	if (input->KeyPress(KEY_R)) {
        Search();
        int n = path->GetPathLength();
        pivot = path;
	}

    if (input->KeyPress(SPACE) ) {
        if (pivot != nullptr) {
            StatePosition* state = dynamic_cast<StatePosition*>(pivot->GetState());
            Position p = state->GetPosition();
            this->MoveTo(p);
            int n = pivot->GetPathLength();
            pivot = pivot->Father();
        }
        else {
            pivot = path;
            MoveTo(initial);
        }
    }
}

void Player::OnCollision(Object* obj) {

}

void deletePath(Node* path) {
    Node* node = path;
    while (node != nullptr) {
        Node* aux = node;
        node = node->Father();
        delete aux->GetState();
        delete aux;
    }
}

void Player::Search() {
    StatePosition* A = new StatePosition(this->GetPosition());
    StatePosition* B = new StatePosition(target);

    std::string s = "";
    OutputDebugString("------------");
    if (path) {
        deletePath(path);
    }
    path = SearchMethods::HeuristicSearch(A, B, actions);
    int value = path->GetPathLength();
    /*s = "\nHeuristic: {\n\t" + path->GetPath() + "\n}\n\tCost: " + std::to_string(path->Cost());
    OutputDebugString(s.c_str());*/
}



void Player::SetTarget(const Position& p) {
    target = p;
}


