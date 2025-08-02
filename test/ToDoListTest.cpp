//
// Created by adria on 02/08/2025.
//

#include "gtest/gtest.h"
#include "TodoList.h" // Includiamo l'header della classe da testare
#include <fstream>    // Necessario per la gestione dei file
#include <cstdio>     // Necessario per std::remove

// Definiamo una Test Fixture per evitare di ripetere il codice di setup
class TodoListTest : public ::testing::Test {
protected:
    // Oggetti che saranno disponibili in ogni test di questa suite
    TodoList list;
    const std::string testFilename = "test_todolist.txt";

    // Il metodo SetUp() viene eseguito PRIMA di ogni test
    void SetUp() override {
        // Creiamo una lista con due task per i nostri test
        list.addTask("Task 1");
        list.addTask("Task 2");
    }

    // Il metodo TearDown() viene eseguito DOPO ogni test
    void TearDown() override {
        // Rimuoviamo il file di test per non lasciare "sporcizia"
        // e garantire che i test siano indipendenti.
        std::remove(testFilename.c_str());
    }
};

// Usiamo TEST_F per indicare che questo test usa la Fixture 'TodoListTest'
TEST_F(TodoListTest, AddTask) {
    // La lista ha già 2 task grazie a SetUp()
    ASSERT_EQ(list.getTasks().size(), 2);

    list.addTask("Task 3");

    ASSERT_EQ(list.getTasks().size(), 3);
    EXPECT_EQ(list.getTasks().back().getDescription(), "Task 3");
    EXPECT_FALSE(list.getTasks().back().isCompleted());
}

TEST_F(TodoListTest, MarkTaskAsCompleted) {
    // Prendiamo l'ID del primo task
    int taskId = list.getTasks().front().getId();

    bool result = list.markTaskAsCompleted(taskId);

    EXPECT_TRUE(result); // L'operazione dovrebbe avere successo
    EXPECT_TRUE(list.getTasks().front().isCompleted());

    // Verifichiamo il comportamento con un ID non esistente
    EXPECT_FALSE(list.markTaskAsCompleted(999));
}

TEST_F(TodoListTest, RemoveTask) {
    // Prendiamo l'ID del primo task
    int taskId = list.getTasks().front().getId();

    bool result = list.removeTask(taskId);

    EXPECT_TRUE(result); // L'operazione dovrebbe avere successo
    ASSERT_EQ(list.getTasks().size(), 1); // La dimensione della lista deve diminuire

    // Verifichiamo il comportamento con un ID non esistente
    EXPECT_FALSE(list.removeTask(999));
}

TEST_F(TodoListTest, SaveAndLoadFromFile) {
    // 1. Modifichiamo lo stato per renderlo più interessante
    list.markTaskAsCompleted(list.getTasks().front().getId());

    // 2. Salviamo la lista corrente su file
    ASSERT_TRUE(list.saveToFile(testFilename));

    // 3. Creiamo una nuova lista vuota
    TodoList newList;

    // 4. Carichiamo i dati dal file nella nuova lista
    ASSERT_TRUE(newList.loadFromFile(testFilename));

    // 5. Verifichiamo che la nuova lista sia identica a quella vecchia
    const auto& originalTasks = list.getTasks();
    const auto& loadedTasks = newList.getTasks();

    ASSERT_EQ(loadedTasks.size(), originalTasks.size());
    for (size_t i = 0; i < originalTasks.size(); ++i) {
        EXPECT_EQ(loadedTasks[i].getId(), originalTasks[i].getId());
        EXPECT_EQ(loadedTasks[i].getDescription(), originalTasks[i].getDescription());
        EXPECT_EQ(loadedTasks[i].isCompleted(), originalTasks[i].isCompleted());
    }
}

TEST_F(TodoListTest, LoadFromNonExistentFile) {
    TodoList emptyList;
    // Tentare di caricare da un file che non esiste non dovrebbe essere un errore,
    // ma dovrebbe semplicemente risultare in una lista vuota.
    EXPECT_FALSE(emptyList.loadFromFile("non_existent_file.txt"));
    EXPECT_TRUE(emptyList.getTasks().empty());
}