#include "wrappers/mysql/MySqlPreparedStatement.h"
#include "wrappers/mysql/MySqlResultBinder.h"

#include <iostream>
#include <mysql.h>


MySqlPreparedStatement::MySqlPreparedStatement(MYSQL * connection){
    std::cout << "Construyendo objeto MySqlPreparedStatement" << std::endl;
    this->connection = connection;
}

MySqlPreparedStatement::~MySqlPreparedStatement(){
    std::cout << "Destruyendo objeto MySqlPreparedStatement" << std::endl;
}

void MySqlPreparedStatement::setQuery(std::string query){
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
    floatStorage.push_back(value); // guarda una copia
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

std::vector<MySqlResultBinder> MySqlPreparedStatement::executeQuery(){
    MYSQL_STMT *statement = this->getMySqlStatement();
    std::vector<MySqlResultBinder> results;

    if (mysql_stmt_execute(statement)) {
        std::cerr << "Error al ejecutar: " << mysql_stmt_error(statement) << std::endl;
        return results;
    }

    MYSQL_RES *metadata = mysql_stmt_result_metadata(statement);
    unsigned int fieldCount = mysql_num_fields(metadata);

    auto binder = std::make_unique<MySqlResultBinder>(fieldCount);

    mysql_stmt_bind_result(statement, binder->data());
    mysql_stmt_store_result(statement);

    while (mysql_stmt_fetch(statement) == 0) {
        MySqlResultBinder rowCopy = binder->clone();
        results.push_back(std::move(rowCopy));
        
        for (unsigned int i = 0; i < fieldCount; ++i) {
            if (binder->getIsNull()[i]) {
                std::cout << "Campo " << i << ": NULL" << std::endl;
            } else {
                std::cout << "Campo " << i << ": "
                        << binder->getString(i) << std::endl;
            }
        }
    }

    mysql_stmt_free_result(statement);
    mysql_stmt_close(statement);

    return results;
}

MYSQL_STMT * MySqlPreparedStatement::getMySqlStatement(){
    MYSQL_STMT * statement = mysql_stmt_init(this->connection);
    MYSQL_BIND * bindings = this->bindings.data();
    
    if (mysql_stmt_prepare(statement, this->query.c_str(), this->query.length())) {
        std::cerr << "[ERROR] MySqlPreparedStatement::getMySqlStatement al invocar mysql_stmt_prepare(): " << mysql_stmt_error(statement) << std::endl;
    }

    if (mysql_stmt_bind_param(statement, bindings)) {
        std::cerr << "[ERROR] MySqlPreparedStatement::getMySqlStatement al invocar mysql_stmt_bind_param(): " << mysql_stmt_error(statement) << std::endl;
    }

    return statement;
}