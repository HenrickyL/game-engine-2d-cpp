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

    DictionaryStatus status = Enabled; // Status inicial � habilitado

public:
    // Construtor
    Dictionary() {}

    // M�todo para habilitar o dicion�rio
    void Enable() {
        status = Enabled;
    }

    // M�todo para desabilitar o dicion�rio
    void Disable() {
        status = Disabled;
    }

    // M�todo para verificar se o dicion�rio est� habilitado
    bool IsEnabled() const {
        return status == Enabled;
    }

    // M�todo para adicionar um par chave-valor ao dicion�rio
    void Add(const KeyType& key, State* value) {
        if (IsEnabled()) {
            dictionary[key] = value;
        }
    }

    // M�todo para consultar o valor associado a uma chave no dicion�rio
    bool Get(const KeyType& key, State*& value) const {
        auto it = dictionary.find(key);
        if (it != dictionary.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    // M�todo para verificar se uma chave est� no dicion�rio
    bool Contains(const KeyType& key) const {
        return dictionary.find(key) != dictionary.end();
    }

    // M�todo para remover um par chave-valor do dicion�rio
    void Remove(const KeyType& key) {
        if (IsEnabled()) {
            dictionary.erase(key);
        }
    }

    // M�todo para obter o valor associado a uma chave
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