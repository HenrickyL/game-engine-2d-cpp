#ifndef IA_DICTIONARY_H
#define IA_DICTIONARY_H
//------------------------------------------
//#include "State.h"
#include "Hasheable.h"
#include <unordered_map>
//------------------------------------------
enum DictionaryStatus { Enabled, Disabled };
//------------------------------------------
template <typename KeyType>
class State;


//// Agora, defina seu pr�prio comparador para KeyType
//struct KeyTypeEqual {
//    template <typename T>
//    bool operator()(const T& a, const T& b) const {
//        return a == b;
//    }
//};


template <typename KeyType>
class Dictionary {
private:
    // Defina seu pr�prio hasher para KeyType
    struct KeyTypeHash {
        template <typename T>
        std::size_t operator()(const T& key) const {
            const Hasheable* myKey = dynamic_cast<const Hasheable*>(&key);
            if (myKey) {
                return myKey->customHash();
            }
            else {
                throw "<Hasheable> key is not Hasheable!";
            }
        }
    };
    std::unordered_map<KeyType, State<KeyType>*, KeyTypeHash> dictionary;
    // Enum para o status

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
    void Add(const KeyType& key, State<KeyType>* value) {
        if (IsEnabled()) {
            dictionary[key] = value;
        }
    }

    // M�todo para consultar o valor associado a uma chave no dicion�rio
    bool ContainKeyByValue(const KeyType& key, State<KeyType>*& value) const {
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
    State<KeyType>* Get(const KeyType& key) const {
        auto it = dictionary.find(key);
        if (it != dictionary.end()) {
            return it->second;
        }
        return nullptr;
    }
    //------------------------------------------

    Dictionary& operator=(const std::pair<KeyType, State<KeyType>*>& pair) {
        dictionary[pair.first] = pair.second;
        return *this;
    }

    State<KeyType>*& operator[](const KeyType& key) {
        return dictionary[key];
    }
};

#endif