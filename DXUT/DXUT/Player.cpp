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

    interTimer = new Timer();
    dictionary = new Dictionary<Position>();

    MovimentAction* N = new MovimentAction(Vector::Up);
    MovimentAction* S = new MovimentAction(Vector::Down);
    MovimentAction* W = new MovimentAction(Vector::Left);
    MovimentAction* E = new MovimentAction(Vector::Right);

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
    actions.push_back(NE);
    actions.push_back(E);
    actions.push_back(SE);
    actions.push_back(S);
    actions.push_back(SW);
    actions.push_back(W);
    actions.push_back(NW);
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
    if (interTimer) delete interTimer;
}



void Player::Update() {
	if (input->KeyPress(KEY_R)) {
        Search();
        pivot = path;
        _sprite->SetFilterColor(Color(0, 255, 0));
	}
    
    if (input->KeyDown(KEY_O)) {
        _sprite->SetFilterColor(Color(255, 0, 0));
        MoveTo(initial);
    }


    if (input->KeyDown(SPACE) ) {
        run = true;
        interTimer->Stop();
        interTimer->Start();
    }
    if (input->KeyDown(VK_RIGHT)) {
        _sprite->SetFilterColor(Color(255, 0, 0));
        StatePosition p(GetPosition());
        Position current=actions[E]->Apply(&p);
        MoveTo(current);
    }else if (input->KeyDown(VK_LEFT)) {
        _sprite->SetFilterColor(Color(255, 0, 0));
        StatePosition p(GetPosition());
        Position current = actions[W]->Apply(&p);
        MoveTo(current);
    }else if (input->KeyDown(VK_UP)) {
        _sprite->SetFilterColor(Color(255, 0, 0));
        StatePosition p(GetPosition());
        Position current = actions[N]->Apply(&p);
        MoveTo(current);
    }
    else if (input->KeyDown(VK_DOWN)) {
        _sprite->SetFilterColor(Color(255, 0, 0));
        StatePosition p(GetPosition());
        Position current = actions[S]->Apply(&p);
        MoveTo(current);
    }


    if (run && interTimer->Elapsed(animationTime / ( pathLength != 0 ? pathLength : 1))) {
        interTimer->Reset();
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
            run = false;
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
    Timer t;
    t.Start();
    path = SearchMethods<Position>::HeuristicSearch(A, B, actions, dictionary, HillClimb);
    t.Stop();
    timer = t.Elapsed();
    pathLength = path != nullptr ? path->GetPathLength() : 0;
}



void Player::SetTarget(const Position& p) {
    target = p;
}


