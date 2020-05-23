# Компиляция
g++ -Wall -o lexer lexer.cpp

# Запуск:
./lexer <file> <options>
или
./lexer <file>

# Для запуска тестов необходимо в lexer.cpp раскоментировать строчку 7
//#define CATCH_CONFIG_MAIN

Для тестирования используется файл
catch.hpp
