//
// Created by adria on 02/08/2025.
//

#include "TodoList.h"
#include <fstream>
#include <iostream>
#include <algorithm> // Per std::remove_if

TodoList::TodoList() : nextId(1) {}

void TodoList::addTask(const std::string& description) {
    tasks.emplace_back(nextId++, description);
}

const std::vector<Task>& TodoList::getTasks() const {
    return tasks;
}

// NOLINTNEXTLINE(readability-make-member-function-const)
bool TodoList::markTaskAsCompleted(const int taskId) { // falso positivo (warning)
    for (auto& task : tasks) {
        if (task.getId() == taskId) {
            task.markAsCompleted();
            return true;
        }
    }
    return false; // Task non trovato
}

bool TodoList::removeTask(int taskId) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
                             [taskId](const Task& task) {
                                 return task.getId() == taskId;
                             });

    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        return true;
    }
    return false; // Task non trovato
}

bool TodoList::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Errore: Impossibile aprire il file in scrittura: " << filename << std::endl;
        return false;
    }

    for (const auto& task : tasks) {
        // Usiamo la 'x' per la massima compatibilità
        outFile << "[" << (task.isCompleted() ? "x" : " ") << "] "
                << task.getId() << ": "
                << task.getDescription() << "\n";
    }
    return true;
}

bool TodoList::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false;
    }

    tasks.clear();
    int maxId = 0;
    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        try {
            // Troviamo le posizioni dei delimitatori chiave
            size_t closingBracketPos = line.find(']');
            size_t colonPos = line.find(':');

            // Se i delimitatori non ci sono, la riga non è valida
            if (closingBracketPos == std::string::npos || colonPos == std::string::npos || closingBracketPos > colonPos) {
                continue;
            }

            // Estraiamo lo stato (completato/non completato)
            bool completed = (line.substr(1, closingBracketPos - 1).find('x') != std::string::npos);

            // Estraiamo l'ID (tra ']' e ':')
            std::string idStr = line.substr(closingBracketPos + 1, colonPos - (closingBracketPos + 1));
            int id = std::stoi(idStr);

            // Estraiamo la descrizione (dopo ': ')
            std::string description = line.substr(colonPos + 2);

            tasks.emplace_back(id, description, completed);

            if (id > maxId) {
                maxId = id;
            }
        } catch (const std::exception& e) {
            std::cerr << "Attenzione: riga malformata ignorata: " << line << std::endl;
        }
    }

    nextId = maxId + 1;
    return true;
}