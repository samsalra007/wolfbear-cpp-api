#include <iostream>
#include <string>

#include <mysql.h>
#include "wrappers/MySqlWrapper.h"

MySqlWrapper::MySqlWrapper(){
    std::cout << "Construyendo objeto MySqlWrapper" << std::endl;
    this->host = "localhost";
    this->port = 3306;
    this->username = "wolfbear_user";
    this->password = "welcome";
    this->database = "wolfbear_os";
}

MySqlWrapper::MySqlWrapper(const std::string host, int port, const std::string username, const std::string password){
    std::cout << "Construyendo objeto MySqlWrapper" << std::endl;
    this->host = host;
    this->port = port;
    this->username = username;
    this->password = password;
}

MySqlWrapper::~MySqlWrapper(){
    std::cout << "Destruyendo objeto MySqlWrapper" << std::endl;

    std::cout << "Intentando verificar si existe una conexion activa a MySQL" << std::endl;
    if( this->connection != NULL && mysql_ping(this->connection) == 0 ){
        std::cout << "Se encontro una conexion activa, procediendo a cerrarla" << std::endl;
        mysql_close(this->connection);
    } else {
        std::cout << "No se encontro una conexion activa a MySQL" << std::endl;
    }
}

MYSQL * MySqlWrapper::getConnection(){
    return this->connection;
}

bool MySqlWrapper::connect(){
    this->connection = mysql_init(nullptr);
    if(!this->connection){
        std::cout << "No fue posible inicializar el objeto de conexion MySQL" << std::endl;
        return false;
    }

    if(!mysql_real_connect(
        this->connection,
        this->host.c_str(),
        this->username.c_str(),
        this->password.c_str(),
        this->database.c_str(),
        this->port, nullptr, 0)){
            std::cout << "Conexion fallida MySQL" << std::endl;
            return false;
    }

    std::cout << "Conexion exitosa a la base de datos MySQL" << std::endl;
    return true;
}

MYSQL_RES* MySqlWrapper::executeQuery(const std::string query){
    if(mysql_query(this->connection, query.c_str())){
        std::cout << "No fue posible ejecutar la consulta" << std::endl;
        mysql_close(this->connection);
        return NULL;
    }

    std::cout << "Obteniendo datos de resultados MySQL" << std::endl;
    
    MYSQL_RES *result = mysql_store_result(this->connection);

    if(!result){
        std::cout << "No fue posible almacenar los datos de resultados" << std::endl;
        mysql_close(this->connection);
        return NULL;
    }

    if(mysql_field_count(this->connection) == 0){
        std::cout << "La consulta realizada no regresa datos ya que es de seleccion" << std::endl;
    }

    return result;
}

void MySqlWrapper::disconnect(){
    mysql_close(this->connection);
}