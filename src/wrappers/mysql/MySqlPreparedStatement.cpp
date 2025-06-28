#include "wrappers/mysql/MySqlPreparedStatement.h"

#include <iostream>

MySqlPreparedStatement::MySqlPreparedStatement(){
    std::cout << "Construyendo objeto MySqlPreparedStatement" << std::endl;
    this->query = "";
}

MySqlPreparedStatement::MySqlPreparedStatement(std::string query){
    std::cout << "Construyendo objeto MySqlPreparedStatement" << std::endl;
    this->query = query;
}

MySqlPreparedStatement::~MySqlPreparedStatement(){
    std::cout << "Destruyendo objeto MySqlPreparedStatement" << std::endl;
}

void MySqlPreparedStatement::setQuery(const std::string query){
    this->query = query;
}

void MySqlPreparedStatement::setString(const std::string value){
    stringStorage.push_back(value);
    const std::string& storedStr = stringStorage.back();

    MYSQL_BIND binding = {};
    binding.buffer_type = MYSQL_TYPE_STRING;
    binding.buffer = (void *) storedStr.c_str();
    binding.buffer_length = storedStr.length();

    bindings.push_back(binding);
}

void MySqlPreparedStatement::setInt(const int value){
    intStorage.push_back(value); // guarda una copia
    int& storedValue = intStorage.back(); // referencia válida

    MYSQL_BIND binding = {};
    binding.buffer_type = MYSQL_TYPE_LONG;
    binding.buffer = (void *) &storedValue;
    binding.is_null = 0;
    binding.length = nullptr; // para enteros no es necesario usualmente

    bindings.push_back(binding);
}

void MySqlPreparedStatement::setFloat(const float value){
    intStorage.push_back(value); // guarda una copia
    float& storedValue = floatStorage.back(); // referencia válida

    MYSQL_BIND binding = {};
    binding.buffer_type = MYSQL_TYPE_LONG;
    binding.buffer = (void *) &storedValue;
    binding.is_null = 0;
    binding.length = nullptr; // para enteros no es necesario usualmente

    bindings.push_back(binding);
}

void MySqlPreparedStatement::clear(){
    this->stringStorage.clear();
    this->floatStorage.clear();
    this->intStorage.clear();
    
    this->bindings.clear();
}
