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

    MovimentAction* up = new MovimentAction(Vector::Up);
    MovimentAction* down = new MovimentAction(Vector::Down);
    MovimentAction* left = new MovimentAction(Vector::Left);
    MovimentAction* right = new MovimentAction(Vector::Right);

    //set inverses
    up->SetInverse(down);
    down->SetInverse(up);
    right->SetInverse(left);
    left->SetInverse(right);

    actions.push_back(up);
    actions.push_back(down);
    actions.push_back(left);
    actions.push_back(right);
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
        Search();
        int n = path->GetPathLength();
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
            MoveTo(initial);
        }
    }
}

void Player::OnCollision(Object* obj) {

}

void deletePath(Node<Position>* _path) {
    Node<Position>* node = _path;
    while (node != nullptr) {
        Node<Position>* aux = node;
        node = node->Father();
        delete aux->GetState();
        delete aux;
    }
}


void Player::Search() {
    StatePosition* A = new StatePosition(this->GetPosition());
    StatePosition* B = new StatePosition(target);

    std::string s = "";
    //OutputDebugString("------------");
    if (path) {
        deletePath(path);
    }
    t->Start();
    path = SearchMethods<Position>::HeuristicSearch(A, B, actions, dictionary);
    t->Stop();
    float timer = t->Elapsed();
    t->Reset();
    int value = path ? path->GetPathLength() : 0;
    /*s = "\nHeuristic: {\n\t" + path->GetPath() + "\n}\n\tCost: " + std::to_string(path->Cost());
    OutputDebugString(s.c_str());*/
}



void Player::SetTarget(const Position& p) {
    target = p;
}


