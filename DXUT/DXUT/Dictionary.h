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
    // Defina seu próprio hasher para KeyType
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
    DictionaryStatus status = Enabled; // Status inicial é habilitado

public:
    // Construtor
    Dictionary();

    // Método para habilitar o dicionário
    void Enable();

    // Método para desabilitar o dicionário
    void Disable();

    // Método para verificar se o dicionário está habilitado
    bool IsEnabled() const;

    // Método para adicionar um par chave-valor ao dicionário
    void Add(const KeyType& key, State<KeyType>* value);

    // Método para consultar o valor associado a uma chave no dicionário
    bool ContainKeyByValue(const KeyType& key, State<KeyType>*& value) const;

    // Método para verificar se uma chave está no dicionário
    bool Contains(const KeyType& key) const;

    // Método para remover um par chave-valor do dicionário
    void Remove(const KeyType& key);

    // Método para obter o valor associado a uma chave
    State<KeyType>* Get(const KeyType& key) const;
    //------------------------------------------

    Dictionary& operator=(const std::pair<KeyType, State<KeyType>*>& pair);

    State<KeyType>*& operator[](const KeyType& key) const;
};

#include "Dictionary.inl"
#endif