#pragma once

#include <memory>
#include <vector>
#include <string>

#include <mysql.h>

class MySqlPreparedStatement{
    private:
        std::string query;
        std::vector<MYSQL_BIND>     bindings;

        std::vector<std::string>    stringStorage;
        std::vector<float>          floatStorage;
        std::vector<int>            intStorage;

    public:
        MySqlPreparedStatement();
        MySqlPreparedStatement(std::string query);
        ~MySqlPreparedStatement();

        void setQuery(const std::string query);
        void setString(const std::string value);
        void setFloat(const float value);
        void setInt(const int value);

        void clear();
};