//
// Created by adria on 02/08/2025.
//

#ifndef TODOLISTPROJECT_TASK_H
#define TODOLISTPROJECT_TASK_H

#include <string>

class Task {
public:
    Task(int id, std::string description, bool completed = false);

    int getId() const;
    const std::string& getDescription() const;
    bool isCompleted() const;

    void markAsCompleted();

private:
    int id;
    std::string description;
    bool completed;
};

#endif //TODOLISTPROJECT_TASK_H