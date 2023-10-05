#ifndef IA_DICTIONARY_H
#define IA_DICTIONARY_H
//------------------------------------------
#include "State.h"
#include <unordered_map>
//------------------------------------------
enum DictionaryStatus { Enabled, Disabled };
//------------------------------------------

template <typename KeyType>
class Dictionary {
//private:
    std::unordered_map<KeyType, State*> dictionary;
    ; // Enum para o status

    DictionaryStatus status = Enabled; // Status inicial é habilitado

public:
    // Construtor
    Dictionary() {}

    // Método para habilitar o dicionário
    void Enable() {
        status = Enabled;
    }

    // Método para desabilitar o dicionário
    void Disable() {
        status = Disabled;
    }

    // Método para verificar se o dicionário está habilitado
    bool IsEnabled() const {
        return status == Enabled;
    }

    // Método para adicionar um par chave-valor ao dicionário
    void Add(const KeyType& key, State* value) {
        if (IsEnabled()) {
            dictionary[key] = value;
        }
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
        if (IsEnabled()) {
            dictionary.erase(key);
        }
    }

    // Método para obter o valor associado a uma chave
    State* Get(const KeyType& key) const {
        auto it = dictionary.find(key);
        if (it != dictionary.end()) {
            return it->second;
        }
        return nullptr;
    }
    //------------------------------------------

    Dictionary& operator=(const std::pair<KeyType, State*>& pair) {
        dictionary[pair.first] = pair.second;
        return *this;
    }
    State*& operator[](const KeyType& key); {
        return dictionary[key];
    }
};

#endif