//
// Created by adria on 02/08/2025.
//

// File: test/TodoListTest.cpp

#include "gtest/gtest.h"
#include "TodoList.h"
#include <fstream>
#include <cstdio> // Per std::remove

class TodoListTest : public ::testing::Test {
protected:
    TodoList list;
    const std::string testFilename = "gtest_temp_todolist.txt";

    void SetUp() override {
        list.addTask("Task 1, con virgola");
        list.addTask("Task 2");
    }

    void TearDown() override {
        std::remove(testFilename.c_str());
    }
};

TEST_F(TodoListTest, AddTask) {
    ASSERT_EQ(list.getTasks().size(), 2);
    list.addTask("Task 3");
    ASSERT_EQ(list.getTasks().size(), 3);
    EXPECT_EQ(list.getTasks().back().getDescription(), "Task 3");
}

TEST_F(TodoListTest, MarkTaskAsCompleted) {
    int taskId = list.getTasks().front().getId();
    ASSERT_TRUE(list.markTaskAsCompleted(taskId));
    EXPECT_TRUE(list.getTasks().front().isCompleted());
    EXPECT_FALSE(list.markTaskAsCompleted(999));
}

TEST_F(TodoListTest, RemoveTask) {
    int taskId = list.getTasks().front().getId();
    ASSERT_TRUE(list.removeTask(taskId));
    ASSERT_EQ(list.getTasks().size(), 1);
    EXPECT_FALSE(list.removeTask(999));
}

TEST_F(TodoListTest, SaveAndLoadFromFile) {
    list.markTaskAsCompleted(list.getTasks().front().getId());

    ASSERT_TRUE(list.saveToFile(testFilename));

    TodoList newList;
    ASSERT_TRUE(newList.loadFromFile(testFilename));

    ASSERT_EQ(newList.getTasks().size(), list.getTasks().size());

    const auto& originalTasks = list.getTasks();
    const auto& loadedTasks = newList.getTasks();
    for (size_t i = 0; i < originalTasks.size(); ++i) {
        EXPECT_EQ(loadedTasks[i].getId(), originalTasks[i].getId());
        EXPECT_EQ(loadedTasks[i].getDescription(), originalTasks[i].getDescription());
        EXPECT_EQ(loadedTasks[i].isCompleted(), originalTasks[i].isCompleted());
    }
}

TEST(TodoListStandaloneTest, LoadFromNonExistentFile) {
    TodoList list;
    EXPECT_FALSE(list.loadFromFile("un_file_che_non_esiste.txt"));
    EXPECT_EQ(list.getTasks().size(), 0);
}