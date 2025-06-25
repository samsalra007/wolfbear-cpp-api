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
        
        MYSQL_RES * executeQuery(const std::string query);
        MYSQL * getConnection();

        void disconnect();
};