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
        outFile << task.getId() << ","
                << task.isCompleted() << ","
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
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);


        if (pos1 == std::string::npos || pos2 == std::string::npos) {
            continue; // Salta questa riga del file se non è valida
        }

        int id = std::stoi(line.substr(0, pos1));
        bool completed = (std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1)) != 0);
        std::string description = line.substr(pos2 + 1);

        tasks.emplace_back(id, description, completed);

        if (id > maxId) {
            maxId = id;
        }
    }

    nextId = maxId + 1;
    return true;
}