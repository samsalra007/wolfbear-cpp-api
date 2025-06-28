#pragma once

#include <memory>
#include <vector>
#include <mysql.h>

class MySqlResultBinder {
    public:
        std::vector<std::vector<char>> buffers;
        std::vector<unsigned long> lengths;
        std::vector<my_bool> isNull;
        std::vector<MYSQL_BIND> bindings;

        void addStringField(size_t maxSize);
        
        MYSQL_BIND* data();
        size_t size() const;
        std::string getString(size_t index) const;
        void setLength(size_t index, unsigned long len);
};