#ifndef DXUT_FILE_HANDLER_H
#define DXUT_FILE_HANDLER_H

#include <vector>
#include <string>

class FileHandler {
private:
    std::vector<std::string> fileLines; // Vetor de strings representando as linhas do arquivo
    std::string filePath; // Caminho do arquivo

public:
    FileHandler(const std::string& path); // Construtor que aceita o caminho do arquivo
    ~FileHandler(); // Destrutor

    bool Read(); // Ler o conte�do do arquivo
    void Write(const std::string& data); // Escrever dados no arquivo
    void Append(const std::string& data); // Adicionar dados ao final do arquivo
    void Save(); // Salvar todas as linhas no arquivo

    const std::vector<std::string>& GetLines() const; // Obter todas as linhas como refer�ncia constante
};

#endif
