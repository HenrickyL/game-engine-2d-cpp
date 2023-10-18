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
    Dictionary();

    // M�todo para habilitar o dicion�rio
    void Enable();

    // M�todo para desabilitar o dicion�rio
    void Disable();

    // M�todo para verificar se o dicion�rio est� habilitado
    bool IsEnabled() const;

    // M�todo para adicionar um par chave-valor ao dicion�rio
    void Add(const KeyType& key, State<KeyType>* value);

    // M�todo para consultar o valor associado a uma chave no dicion�rio
    bool ContainKeyByValue(const KeyType& key, State<KeyType>*& value) const;

    // M�todo para verificar se uma chave est� no dicion�rio
    bool Contains(const KeyType& key) const;

    // M�todo para remover um par chave-valor do dicion�rio
    void Remove(const KeyType& key);

    // M�todo para obter o valor associado a uma chave
    State<KeyType>* Get(const KeyType& key) const;
    //------------------------------------------

    Dictionary& operator=(const std::pair<KeyType, State<KeyType>*>& pair);

    State<KeyType>*& operator[](const KeyType& key) const;
};

#include "Dictionary.inl"
#endif