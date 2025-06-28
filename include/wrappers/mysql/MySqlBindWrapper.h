#include <string>
#include <vector>

#include <mysql.h>

class MySqlBindWrapper {
    private:
        std::vector<MYSQL_BIND> bindings;
        std::vector<std::string> stringStorage;
        std::vector<int> intStorage;
        std::vector<float> floatStorage;

    public:
        MySqlBindWrapper();
        ~MySqlBindWrapper();

        void bindString(const std::string value);
        void bindInt(const int value);
        void bindFloat(const float value);
        void clear();
        
        MYSQL_BIND * getBindArray();
};
