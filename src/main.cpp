#include <iostream>
#include "TodoList.h"

void printMenu() {
    std::cout << "\n--- Todo List Menu ---\n";
    std::cout << "1. Mostra attivita'\n";
    std::cout << "2. Aggiungi attivita'\n";
    std::cout << "3. Segna attivita' come completata\n";
    std::cout << "4. Rimuovi attivita'\n";
    std::cout << "5. Salva ed esci\n";
    std::cout << "Scegli un'opzione: ";
}

void displayTasks(const TodoList& list) {
    std::cout << "\n--- Le tue attivita' ---\n";
    if (list.getTasks().empty()) {
        std::cout << "Nessuna attivita' presente.\n";
        return;
    }
    for (const auto& task : list.getTasks()) {
        std::cout << "[" << (task.isCompleted() ? "x" : " ") << "] "
                  << task.getId() << ": "
                  << task.getDescription() << std::endl;
    }
}

int main() {
    TodoList list;
    const std::string filename = "data/todolist.txt";
    list.loadFromFile(filename);

    int choice;
    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(); // Pulisce il buffer di input

        switch (choice) {
            case 1:
                displayTasks(list);
                break;
            case 2: {
                std::cout << "Inserisci la descrizione della nuova attivita': ";
                std::string description;
                std::getline(std::cin, description);
                list.addTask(description);
                std::cout << "Attivita' aggiunta.\n";
                break;
            }
            case 3: {
                std::cout << "Inserisci l'ID dell'attivita' da completare: ";
                int id;
                std::cin >> id;
                if (list.markTaskAsCompleted(id)) {
                    std::cout << "Attivita' segnata come completata.\n";
                } else {
                    std::cout << "Errore: ID non trovato.\n";
                }
                break;
            }
            case 4: {
                std::cout << "Inserisci l'ID dell'attivita' da rimuovere: ";
                int id;
                std::cin >> id;
                if (list.removeTask(id)) {
                    std::cout << "Attivita' rimossa.\n";
                } else {
                    std::cout << "Errore: ID non trovato.\n";
                }
                break;
            }
            case 5:
                if (list.saveToFile(filename)) {
                    std::cout << "Salvataggio completato. Arrivederci!\n";
                } else {
                    std::cout << "Errore durante il salvataggio.\n";
                }
                break;
            default:
                std::cout << "Scelta non valida. Riprova.\n";
        }
    } while (choice != 5);

    return 0;
}