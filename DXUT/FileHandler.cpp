#include "FileHandler.h"
#include <fstream>
#include <iostream> // Para output de erros
#include <filesystem>

FileHandler::FileHandler(const std::string& path) : path(path) {
    // Construtor, inicializa o caminho do arquivo
    SetUsername();
}

FileHandler::FileHandler() {
    SetUsername();
    path = "C:\\Users\\"+username+"\\Documents\\GAME_Search_Result\\";
    // Construtor, inicializa o caminho do arquivo
}

FileHandler::~FileHandler() {
    // Destrutor
    if(!saved)
        Save(); // Salva as alterações no arquivo antes de destruir a instância
}


void FileHandler::SetUsername() {
    char userName[MAX_PATH];
    DWORD usernameSize = sizeof(userName);
    GetUserNameA(userName, &usernameSize);
    username = std::string(userName);
}

bool FileHandler::Read() {
    std::ifstream fileStream(path);

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
    saved = false;
    fileLines.clear(); // Limpa as linhas existentes
    fileLines.push_back(data); // Adiciona a nova linha
}

void FileHandler::Append(const std::string& data) {
    saved = false;
    fileLines.push_back(data); // Adiciona a nova linha ao final do vetor
}

void FileHandler::Save(std::string fileName) {
    std::string pathF = path + fileName;
    std::ofstream fileStream(pathF);

    // Cria o diretório se não existir
    std::filesystem::path directory = std::filesystem::path(path);
    if (!std::filesystem::exists(directory)) {
        if (!std::filesystem::create_directories(directory)) {
            std::cerr << "Failed to create directory: " << path << std::endl;
            return;
        }
    }

    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file for writing: " << pathF << std::endl;
        return;
    }

    for (const auto& line : fileLines) {
        fileStream << line << '\n';
    }

    fileStream.close();
    saved = true;
}

const std::vector<std::string>& FileHandler::GetLines() const {
    return fileLines; // Retorna todas as linhas como referência constante
}
