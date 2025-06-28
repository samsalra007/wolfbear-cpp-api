#include "wrappers/mysql/MySqlResultBinder.h"

#include <memory>
#include <vector>
#include <mysql.h>

#include <iostream>

void MySqlResultBinder::addStringField(size_t maxSize) {
    buffers.emplace_back(maxSize);
    lengths.emplace_back(0);
    isNull.emplace_back(0);

    MYSQL_BIND bind = {};
    bind.buffer_type = MYSQL_TYPE_STRING;
    bind.buffer = buffers.back().data();
    bind.buffer_length = maxSize;
    bind.length = &lengths.back();
    bind.is_null = &isNull.back();

    bindings.push_back(bind);
}

MYSQL_BIND * MySqlResultBinder::data() {
    return bindings.data();
}

size_t MySqlResultBinder::size() const {
    return bindings.size();
}

std::string MySqlResultBinder::getString(size_t index) const {
    if (index >= buffers.size()) {
        std::cerr << "getString index out of bounds: " << index << std::endl;
        return "";
    }
    return std::string(buffers[index].data(), lengths[index]);
}

void MySqlResultBinder::setLength(size_t index, unsigned long len) {
    if (index < lengths.size()) {
        lengths[index] = len;
    }
}
