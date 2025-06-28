#include "wrappers/mysql/MySqlBindWrapper.h"

#include <mysql.h>
#include <vector>

MySqlBindWrapper::MySqlBindWrapper(){
    
}

MySqlBindWrapper::~MySqlBindWrapper(){
    
}

void MySqlBindWrapper::bindString(const std::string value){
    stringStorage.push_back(value);
    const std::string& storedStr = stringStorage.back();

    MYSQL_BIND binding = {};
    binding.buffer_type = MYSQL_TYPE_STRING;
    binding.buffer = (void *) storedStr.c_str();
    binding.buffer_length = storedStr.length();

    bindings.push_back(binding);
}

void MySqlBindWrapper::bindInt(const int value){
    intStorage.push_back(value); // guarda una copia
    int& storedValue = intStorage.back(); // referencia válida

    MYSQL_BIND binding = {};
    binding.buffer_type = MYSQL_TYPE_LONG;
    binding.buffer = (void *) &storedValue;
    binding.is_null = 0;
    binding.length = nullptr; // para enteros no es necesario usualmente

    bindings.push_back(binding);
}

void MySqlBindWrapper::bindFloat(const float value){
    intStorage.push_back(value); // guarda una copia
    float& storedValue = floatStorage.back(); // referencia válida

    MYSQL_BIND binding = {};
    binding.buffer_type = MYSQL_TYPE_LONG;
    binding.buffer = (void *) &storedValue;
    binding.is_null = 0;
    binding.length = nullptr; // para enteros no es necesario usualmente

    bindings.push_back(binding);
}

MYSQL_BIND * MySqlBindWrapper::getBindArray(){
    return this->bindings.data();
}

void MySqlBindWrapper::clear(){
    this->stringStorage.clear();
    this->floatStorage.clear();
    this->intStorage.clear();
    
    this->bindings.clear();
}