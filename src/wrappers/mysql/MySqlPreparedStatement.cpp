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

std::unique_ptr<MySqlResultBinder> MySqlPreparedStatement::executeQuery(){
    MYSQL_STMT *statement = this->getMySqlStatement();
    auto binder = std::make_unique<MySqlResultBinder>();

    if (mysql_stmt_execute(statement)) {
        std::cerr << "Error al ejecutar: " << mysql_stmt_error(statement) << std::endl;
        return nullptr;
    }

    MYSQL_RES *metadata = mysql_stmt_result_metadata(statement);
    unsigned int fieldCount = mysql_num_fields(metadata);
    
    std::cout << "Field count: " << fieldCount << std::endl;

    std::vector<std::vector<char>> bufferData(fieldCount);
    std::vector<MYSQL_BIND> binds(fieldCount);
    std::vector<unsigned long> lengths(fieldCount);
    std::vector<my_bool> isNull(fieldCount);

    for (unsigned int i = 0; i < fieldCount; ++i) {
        bufferData[i].resize(256); // espacio fijo por ahora
        memset(&binds[i], 0, sizeof(MYSQL_BIND));
        binds[i].buffer_type = MYSQL_TYPE_STRING;
        binds[i].buffer = bufferData[i].data();
        binds[i].buffer_length = bufferData[i].size();
        binds[i].length = &lengths[i];
        binds[i].is_null = &isNull[i];
    }

    // Bindea buffers de salida
    mysql_stmt_bind_result(statement, binds.data());
    mysql_stmt_store_result(statement);

    // Fetch y lectura
    while (mysql_stmt_fetch(statement) == 0) {
        for (unsigned int i = 0; i < fieldCount; ++i) {
            if (isNull[i]) {
                std::cout << "Campo " << i << ": NULL" << std::endl;
            } else {
                std::cout << "Campo " << i << ": "
                        << std::string(bufferData[i].data(), lengths[i]) << std::endl;
            }
        }
    }
    
    return binder;
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