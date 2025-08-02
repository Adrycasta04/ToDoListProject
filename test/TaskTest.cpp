//
// Created by adria on 02/08/2025.
//

#include "gtest/gtest.h"
#include "Task.h" // Includiamo l'header della classe da testare

// Test Case per la classe Task
// TEST(NomeTestSuite, NomeTest)

// Questo test verifica che il costruttore inizializzi correttamente
// gli attributi e che i metodi getter restituiscano i valori giusti.
TEST(TaskTest, ConstructorAndGetters) {
    // 1. Preparazione (Arrange)
    Task task(1, "Test Description");

    // 2. Azione (Act) - In questo caso, l'azione è la creazione stessa.

    // 3. Verifica (Assert)
    EXPECT_EQ(task.getId(), 1);
    EXPECT_EQ(task.getDescription(), "Test Description");
    EXPECT_FALSE(task.isCompleted()); // Un nuovo task non deve essere completato
}

// Questo test verifica che il metodo markAsCompleted() cambi
// correttamente lo stato del task.
TEST(TaskTest, MarkAsCompleted) {
    // 1. Preparazione (Arrange)
    Task task(2, "Another task");

    // 2. Azione (Act)
    task.markAsCompleted();

    // 3. Verifica (Assert)
    EXPECT_TRUE(task.isCompleted());
}


