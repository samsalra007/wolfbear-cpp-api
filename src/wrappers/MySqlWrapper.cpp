#include <iostream>
#include <string>

#include <mysql.h>
#include "wrappers/MySqlWrapper.h"

MySqlWrapper::MySqlWrapper(){
    this->host = "localhost";
    this->port = 3306;
    this->username = "wolfbear_user";
    this->password = "welcome";
    this->database = "wolfbear_os";
}

MySqlWrapper::MySqlWrapper(const std::string host, int port, const std::string username, const std::string password){
    this->host = host;
    this->port = port;
    this->username = username;
    this->password = password;
}

void MySqlWrapper::connect(){
    this->connection = mysql_init(nullptr);
    if(!this->connection){
        std::cout << "No fue posible inicializar el objeto de conexion MySQL" << std::endl;
        return;
    }

    if(!mysql_real_connect(
        this->connection,
        this->host.c_str(),
        this->username.c_str(),
        this->password.c_str(),
        this->database.c_str(),
        this->port, nullptr, 0)){
            std::cout << "Conexion fallida MySQL" << std::endl;
            return;
    }

    std::cout << "Conexion exitosa a la base de datos MySQL" << std::endl;

    if(mysql_query(this->connection, "SELECT * FROM players ")){
        std::cout << "No fue posible ejecutar la consulta" << std::endl;
        mysql_close(this->connection);
        return;
    }

    std::cout << "Obteniendo datos de resultados MySQL" << std::endl;

    MYSQL_RES *result = mysql_store_result(this->connection);
    if(!result){
        std::cout << "No fue posible almacenar los datos de resultados" << std::endl;
        mysql_close(this->connection);
        return;
    }

    std::cout << "Resultados de la consulta" << std::endl;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        std::cout << "ID: " << row[0] << ", Username: " << row[1] << "\n";
    }

    std::cout << "Cerrando conexion MySQL" << std::endl;

    mysql_free_result(result);
    mysql_close(this->connection);
}