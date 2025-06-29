#pragma once

#include <string>

class WolfbearIdGenerator {
    private:
        static std::string generateId(const std::string & prefix);

    public:
        static std::string generateUserId();
        static std::string generateProfileId();
        static uint64_t getEpochUnixTimestamp();
};