#pragma once
#include <string>

#include <mysql.h>

class MySqlWrapper {
    private:
        std::string host;
        int port;
        std::string database;
        std::string username;
        std::string password;

        MYSQL *connection;

    public:
        MySqlWrapper();
        MySqlWrapper(const std::string host, int port, const std::string username, const std::string password);
        ~MySqlWrapper();
        
        bool connect();
        
        MYSQL_RES   * executeQuery(const std::string query);
        MYSQL_STMT  * createPreparedStatement();
        
        void statementPrepare(MYSQL_STMT * preparedStatement, std::string query);
        void statementBindParams(MYSQL_STMT * preparedStatement, MYSQL_BIND * bindings);
        
        MYSQL * getConnection();

        void disconnect();
};