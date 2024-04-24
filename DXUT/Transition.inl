

template<typename T>
Transition<T>::Transition(State<T>* _origin, State<T>* _target, Action<T>* _act) {
    this->origin = _origin;
    this->target = _target;
    this->action = _act;
}

template<typename T>
State<T>* Transition<T>::GetOrigin() const {
    return origin;
}

template<typename T>
State<T>* Transition<T>::GetTarget() const {
    return target;
}

template<typename T>
Action<T>* Transition<T>::GetAction() const {
    return action;
}