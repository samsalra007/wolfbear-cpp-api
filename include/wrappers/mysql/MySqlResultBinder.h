#pragma once

#include <vector>
#include <mysql.h>

class MySqlResultBinder {
    private:
        std::vector<std::vector<char>>  bufferData;
        std::vector<MYSQL_BIND>         binds;
        std::vector<unsigned long>      lengths;
        std::vector<my_bool>            isNull;
        unsigned int                    fieldCount;
    public:
        MySqlResultBinder(const unsigned int fieldCount);

        MYSQL_BIND* data();
        std::vector<my_bool> getIsNull();
        std::vector<std::vector<char>> getBufferData();
        std::vector<unsigned long> getLengths();

        std::string getString(const unsigned int index);
        MySqlResultBinder clone();
};