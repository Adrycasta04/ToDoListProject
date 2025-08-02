//
// Created by adria on 02/08/2025.
//

#ifndef TODOLISTPROJECT_TODOLIST_H
#define TODOLISTPROJECT_TODOLIST_H

#include "Task.h"
#include <vector>
#include <string>

class TodoList {
public:
    TodoList();

    void addTask(const std::string& description);
    bool markTaskAsCompleted(int taskId);
    bool removeTask(int taskId);

    const std::vector<Task>& getTasks() const;

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

private:
    std::vector<Task> tasks;
    int nextId;
};

#endif //TODOLISTPROJECT_TODOLIST_H