#include "wrappers/mysql/MySqlResultBinder.h"

MySqlResultBinder::MySqlResultBinder(const unsigned int fieldCount){
    bufferData.resize(fieldCount);
    binds.resize(fieldCount);
    lengths.resize(fieldCount);
    isNull.resize(fieldCount);

    for (unsigned int i = 0; i < fieldCount; ++i) {
        bufferData[i].resize(256);
        memset(&binds[i], 0, sizeof(MYSQL_BIND));
        binds[i].buffer_type = MYSQL_TYPE_STRING;
        binds[i].buffer = bufferData[i].data();
        binds[i].buffer_length = bufferData[i].size();
        binds[i].length = &lengths[i];
        binds[i].is_null = &isNull[i];
    }
}

MYSQL_BIND* MySqlResultBinder::data() {
    return binds.data();
}

std::vector<my_bool> MySqlResultBinder::getIsNull(){
    return this->isNull;
}

std::vector<std::vector<char>> MySqlResultBinder::getBufferData(){
    return this->bufferData;
}

std::vector<unsigned long> MySqlResultBinder::getLengths(){
    return this->lengths;
}

std::string MySqlResultBinder::getString(const int unsigned index){
    return std::string(this->bufferData[index].data(), this->getLengths()[index]);
}

MySqlResultBinder MySqlResultBinder::clone(){
    MySqlResultBinder copy(this->fieldCount);

    copy.bufferData = this->bufferData; // std::vector hace copia profunda
    copy.lengths = this->lengths;
    copy.isNull = this->isNull;

    // reconstruir los MYSQL_BINDs para que apunten al nuevo buffer
    copy.binds.resize(this->fieldCount);
    for (unsigned int i = 0; i < this->fieldCount; ++i) {
        MYSQL_BIND& dest = copy.binds[i];

        dest.buffer_type = MYSQL_TYPE_STRING; // o el tipo que estés usando realmente
        dest.buffer = copy.bufferData[i].data();
        dest.buffer_length = copy.bufferData[i].size();
        dest.length = &copy.lengths[i];
        dest.is_null = &copy.isNull[i];
        dest.is_unsigned = 0; // ajusta según necesidad
    }

    return copy;
}