#include "Player.h"
// ------------------------
#include "StatePosition.h"
#include "SearchMethods.h"
// ------------------------

Player::Player(Image* img, const Position& p) {
	_position = new Position(p);
	this->SetSprite(new Sprite(img));
	_magnitude= 100;
	_sprite->SetLayer(Layer::MIDDLE);
    _sprite->SetScale(0.01f);
    _sprite->SetFilterColor(Color(255,0,255));

	BBox(_sprite->GetCircle());

    t = new Timer();
    dictionary = new Dictionary<Position>();

    MovimentAction* N = new MovimentAction(Vector::Up);
    MovimentAction* S = new MovimentAction(Vector::Down);
    MovimentAction* E = new MovimentAction(Vector::Left);
    MovimentAction* W = new MovimentAction(Vector::Right);

    MovimentAction* NE = new MovimentAction(Vector::Right + Vector::Up);
    MovimentAction* NW = new MovimentAction(Vector::Left + Vector::Up);
    MovimentAction* SE = new MovimentAction(Vector::Down + Vector::Right);
    MovimentAction* SW = new MovimentAction(Vector::Down + Vector::Left);


    //set inverses
    N->SetInverse(S);
    S->SetInverse(N);
    W->SetInverse(E);
    E->SetInverse(W);

    NE->SetInverse(SW);
    NW->SetInverse(SE);
    SE->SetInverse(NW);
    SW->SetInverse(NE);

    actions.push_back(N);
    actions.push_back(S);
    actions.push_back(E);
    actions.push_back(W);
    actions.push_back(NE);
    actions.push_back(NW);
    actions.push_back(SE);
    actions.push_back(SW);
    initial = p;

}

Player::~Player() {
    if (_position) delete _position;
    if (_sprite) delete _sprite;
    if (_bbox) delete _bbox;
    for (Action<Position>* a : actions) {
        delete a;
    }
    if (dictionary) delete dictionary;
    if (t) delete t;
}



void Player::Update() {
	if (input->KeyPress(KEY_R)) {
        _sprite->SetFilterColor(Color(255, 0, 0));
        Search();
        pivot = path;
        _sprite->SetFilterColor(Color(0, 255, 0));
	}

    if (input->KeyPress(SPACE) ) {
        if (pivot != nullptr) {
            _sprite->SetFilterColor(Color(255, 255, 255));

            StatePosition* state = dynamic_cast<StatePosition*>(pivot->GetState());
            Position p = state->GetPosition();
            this->MoveTo(p);
            int n = pivot->GetPathLength();
            pivot = pivot->Father();
        }
        else {
            _sprite->SetFilterColor(Color(0, 255, 0));
            pivot = path;
            MoveTo(pivot->Value());
        }
    }
}

void Player::OnCollision(Object* obj) {

}

void deletePath(Node<Position>* _path) {
    Node<Position>* node = _path;
    Node<Position>* aux = nullptr;
    while (node != nullptr) {
        aux = node;
        node = node->Father();
        delete aux;
    }
}


void Player::Search() {
    StatePosition* A = new StatePosition(this->GetPosition());
    StatePosition* B = new StatePosition(target);
    if (path != nullptr) { 
        deletePath(path);
        path = nullptr;
    }
    float timer = 0;
    t->Start();
    path = SearchMethods<Position>::HeuristicSearch(A, B, actions, dictionary);
    t->Stop();
    timer = t->Elapsed();
    int value = path != nullptr ? path->GetPathLength() : 0;
}



void Player::SetTarget(const Position& p) {
    target = p;
}


