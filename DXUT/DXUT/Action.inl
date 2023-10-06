#ifndef ACTION_INL
#define ACTION_INL

template <typename T>
Action<T>::Action(float _cost) {
    cost = _cost;
}

template <typename T>
Action<T>::Action(float _cost, Action<T>* _inverse) {
    cost = _cost;
    inverse = _inverse;
}

template <typename T>
float Action<T>::Cost() const {
    return cost;
}

template <typename T>
Action<T>* Action<T>::Inverse() const {
    return inverse;
}

template <typename T>
void Action<T>::SetInverse(Action<T>* _inverse) {
    inverse = _inverse;
}

#endif
