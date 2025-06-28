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
    MYSQL_STMT* statement = this->getMySqlStatement();

    std::cout << "Intentando ejecutar consulta" << std::endl;
    std::cout << this->query << std::endl;

    // 1. Ejecutar
    if (mysql_stmt_execute(statement)) {
        std::cerr << "Error al ejecutar la consulta: " << mysql_stmt_error(statement) << std::endl;
        return nullptr;
    }

    // 2. Almacenar resultados en memoria (para poder acceder a metadata)
    if (mysql_stmt_store_result(statement)) {
        std::cerr << "Error en mysql_stmt_store_result: " << mysql_stmt_error(statement) << std::endl;
        return nullptr;
    }

    // 3. Obtener metadata del resultado
    MYSQL_RES* metadata = mysql_stmt_result_metadata(statement);
    if (!metadata) {
        std::cerr << "No se pudo obtener metadata del resultado" << std::endl;
        return nullptr;
    }

    unsigned int fieldCount = mysql_num_fields(metadata);
    auto binder = std::make_unique<MySqlResultBinder>();

    // 4. Reservar buffers y estructuras de longitud/nulos
    for (unsigned int i = 0; i < fieldCount; ++i) {
        binder->addStringField(256);  // 256 bytes como tamaño fijo temporal (ajustable)
    }

    // 5. Bind de resultados
    if (mysql_stmt_bind_result(statement, binder->data())) {
        std::cerr << "Error en mysql_stmt_bind_result: " << mysql_stmt_error(statement) << std::endl;
        mysql_free_result(metadata);
        return nullptr;
    }

    // 6. Fetch
    if (mysql_stmt_fetch(statement) != 0) {
        std::cerr << "No se pudo hacer fetch del resultado mysql_stmt_fetch" << std::endl;
        mysql_free_result(metadata);
        return nullptr;
    }

    for (size_t i = 0; i < binder->size(); ++i) {
        std::cout << "[Debug] Columna " << i << ": " << binder->getString(i) << std::endl;
    }

    // 7. Limpieza de metadata (no libera los datos, solo estructura)
    mysql_free_result(metadata);

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