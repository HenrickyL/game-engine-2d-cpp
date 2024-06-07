template <typename T>
void AbstractList<T>::addElement(T element) {
    _elements.push_back(element);
}

template <typename T>
void AbstractList<T>::removeElement(T element) {
    auto it = std::find(_elements.begin(), _elements.end(), element);
    if (it != _elements.end()) {
        _elements.erase(it);
    }
    else {
        throw std::runtime_error("Element not found");
    }
}

template <typename T>
T AbstractList<T>::getElement(size_t index) const {
    if (index >= _elements.size() || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    return _elements[index];
}

template <typename T>
size_t AbstractList<T>::getSize() const {
    return _elements.size();
}
