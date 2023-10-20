//#include "Dictionary.h"

#include "State.h"

template<typename KeyType>
Dictionary<KeyType>::Dictionary() {}

template<typename KeyType>
void Dictionary<KeyType>::Enable() {
    status = Enabled;
}

template<typename KeyType>
void Dictionary<KeyType>::Disable() {
    status = Disabled;
}

template<typename KeyType>
bool Dictionary<KeyType>::IsEnabled() const {
    return status == Enabled;
}

template<typename KeyType>
void Dictionary<KeyType>::Add(const KeyType& key, State<KeyType>* value) {
    if (IsEnabled()) {
        dictionary[key] = value;
    }
}

template<typename KeyType>
bool Dictionary<KeyType>::ContainKeyByValue(const KeyType& key, State<KeyType>*& value) const {
    auto it = dictionary.find(key);
    if (it != dictionary.end()) {
        value = it->second;
        return true;
    }
    return false;
}

template<typename KeyType>
bool Dictionary<KeyType>::Contains(const KeyType& key) const {
    return dictionary.find(key) != dictionary.end();
}

template<typename KeyType>
void Dictionary<KeyType>::Remove(const KeyType& key) {
    if (IsEnabled()) {
        dictionary.erase(key);
    }
}

template<typename KeyType>
State<KeyType>* Dictionary<KeyType>::Get(const KeyType& key) const {
    auto it = dictionary.find(key);
    if (it != dictionary.end()) {
        return it->second;
    }
    return nullptr;
}

template<typename KeyType>
Dictionary<KeyType>& Dictionary<KeyType>::operator=(const std::pair<KeyType, State<KeyType>*>& pair) {
    dictionary[pair.first] = pair.second;
    return *this;
}

template<typename KeyType>
State<KeyType>*& Dictionary<KeyType>::operator[](const KeyType& key) const {
    return dictionary[key];
}