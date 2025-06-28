#include <iostream>
#include <string>
#include <vector>

#include <mysql.h>
#include "wrappers/mysql/MySqlWrapper.h"

MySqlWrapper::MySqlWrapper(){
    std::cout << "Construyendo objeto MySqlWrapper" << std::endl;
}

MySqlWrapper::~MySqlWrapper(){
    std::cout << "Destruyendo objeto MySqlWrapper" << std::endl;
}

MYSQL * MySqlWrapper::connect(const std::string host, int port, const std::string username, const std::string password, const std::string database){
    MYSQL * connection = mysql_init(nullptr);

    if(!connection){
        std::cout << "No fue posible inicializar el objeto de conexion MySQL" << std::endl;
        return NULL;
    }

    if(!mysql_real_connect(
        connection,
        host.c_str(),
        username.c_str(),
        password.c_str(),
        database.c_str(),
        port, nullptr, 0)){
            std::cout << "Conexion fallida a la base de datos MySQL" << std::endl;
    }

    std::cout << "Conexion exitosa a la base de datos MySQL" << std::endl;
    this->connection = connection;
    return connection;
}

std::unique_ptr<MySqlPreparedStatement> MySqlWrapper::prepareStatement(std::string query){
    auto mySqlPreparedStatement = std::make_unique<MySqlPreparedStatement>(this->connection);
    mySqlPreparedStatement->setQuery(query);
    return mySqlPreparedStatement;
}

void MySqlWrapper::disconnect(){
    if(this->connection && mysql_ping(this->connection) == 0){
        mysql_close(this->connection);
    }
}