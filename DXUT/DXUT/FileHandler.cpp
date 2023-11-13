#include "FileHandler.h"
#include <fstream>
#include <iostream> // Para output de erros

FileHandler::FileHandler(const std::string& path) : filePath(path) {
    // Construtor, inicializa o caminho do arquivo
}

FileHandler::~FileHandler() {
    // Destrutor
    Save(); // Salva as alterações no arquivo antes de destruir a instância
}

bool FileHandler::Read() {
    std::ifstream fileStream(filePath);

    if (!fileStream.is_open()) {
        return false; // Falha ao abrir o arquivo
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        fileLines.push_back(line);
    }

    fileStream.close();
    return true;
}

void FileHandler::Write(const std::string& data) {
    fileLines.clear(); // Limpa as linhas existentes
    fileLines.push_back(data); // Adiciona a nova linha
}

void FileHandler::Append(const std::string& data) {
    fileLines.push_back(data); // Adiciona a nova linha ao final do vetor
}

void FileHandler::Save() {
    std::ofstream fileStream(filePath);

    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return;
    }

    for (const auto& line : fileLines) {
        fileStream << line << '\n';
    }

    fileStream.close();
}

const std::vector<std::string>& FileHandler::GetLines() const {
    return fileLines; // Retorna todas as linhas como referência constante
}
