//
// Created by adria on 02/08/2025.
//

#include "Task.h"

Task::Task(int id, std::string description, bool completed)
    : id(id), description(std::move(description)), completed(completed) {}

int Task::getId() const {
    return id;
}

const std::string& Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::markAsCompleted() {
    completed = true;
}