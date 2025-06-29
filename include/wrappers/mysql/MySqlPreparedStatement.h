#pragma once

#include <memory>
#include <vector>
#include <string>

#include <mysql.h>
#include "wrappers/mysql/MySqlResultBinder.h"

class MySqlPreparedStatement{
    private:
        MYSQL           * connection;

        std::string query;
        std::vector<MYSQL_BIND>         bindings;

        std::vector<std::string>    stringStorage;
        std::vector<float>          floatStorage;
        std::vector<int>            intStorage;

    public:
        MySqlPreparedStatement(MYSQL * connection);
        ~MySqlPreparedStatement();

        void setQuery(std::string query);
        void setString(const std::string value);
        void setFloat(const float value);
        void setInt(const std::int32_t value);
        void setEpochTime(const uint64_t value);

        std::vector<MySqlResultBinder> executeQuery();

        void disconnect();
        void disconnect(MYSQL * connection);

        void clear();
    
    private:
        MYSQL_STMT * getMySqlStatement();
};