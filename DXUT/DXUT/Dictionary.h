#ifndef IA_DICTIONARY_H
#define IA_DICTIONARY_H

#include "State.h"
#include <unordered_map>

template <typename KeyType>
class Dictionary {
private:
    std::unordered_map<KeyType, State*> dictionary;

public:
    // Método para adicionar um par chave-valor ao dicionário
    void Add(const KeyType& key, const State*& value) {
        dictionary[key] = value;
    }

    // Método para consultar o valor associado a uma chave no dicionário
    bool Get(const KeyType& key, State*& value) const {
        auto it = dictionary.find(key);
        if (it != dictionary.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    // Método para verificar se uma chave está no dicionário
    bool Contains(const KeyType& key) const {
        return dictionary.find(key) != dictionary.end();
    }

    // Método para remover um par chave-valor do dicionário
    void Remove(const KeyType& key) {
        dictionary.erase(key);
    }

    // Método para obter o valor associado a uma chave
    State* Get(const KeyType& key) const {
        auto it = dictionary.find(key);
        if (it != dictionary.end()) {
            return it->second;
        }
        //throw std::out_of_range("Key not found in dictionary");
        return nullptr;
    }

    // Operador [] para acesso aos valores do dicionário
    State* operator[](const KeyType& key) {
        return dictionary[key];
    }
    // Sobrecarga do operador de atribuição (=)
    ValueType& operator=(const ValueType& value) {
        return dictionary[value.first] = value.second;
    }
};

#endif