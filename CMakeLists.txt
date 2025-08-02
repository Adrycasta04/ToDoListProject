cmake_minimum_required(VERSION 3.30)
project(TodoListProject)

set(CMAKE_CXX_STANDARD 14)

# --- CORREZIONE PRINCIPALE QUI ---
# La libreria "core" deve contenere SOLO i file sorgente dell'applicazione,
# NON i file di test.
add_library(core
        src/Task.cpp
        src/Task.h
        src/TodoList.cpp
        src/TodoList.h
)

# Specifichiamo che gli header per "core" si trovano nella cartella "src"
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Creiamo l'eseguibile principale
add_executable(TodoListApp src/main.cpp)

# Colleghiamo l'eseguibile alla nostra libreria "core"
target_link_libraries(TodoListApp core)

# Aggiungiamo la sottodirectory dei test. CMake la gestirà separatamente.
add_subdirectory(test)