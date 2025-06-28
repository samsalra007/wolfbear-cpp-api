#pragma once

#include <string>
#include <memory>
#include "wrappers/mysql/MySqlPreparedStatement.h"

#include <mysql.h>

class MySqlWrapper {
    private:
        MYSQL * connection;
    public:
        MySqlWrapper();
        ~MySqlWrapper();

        MYSQL * connect(const std::string host, int port, const std::string username, const std::string password, const std::string database);
        std::unique_ptr<MySqlPreparedStatement> prepareStatement (const std::string query);
        
        void disconnect();
};