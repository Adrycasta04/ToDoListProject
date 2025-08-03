# Includi GTest nel nostro progetto
add_subdirectory(lib/googletest)

# Crea l'eseguibile per i test
add_executable(runTests
        runAllTests.cpp
        TaskTest.cpp
        TodoListTest.cpp
)

# Collega l'eseguibile dei test a GTest e alla nostra libreria "core"
# In questo modo, i test possono usare sia GTest sia il codice da testare.
target_link_libraries(runTests GTest::gtest_main core)