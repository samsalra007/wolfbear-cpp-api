#include "utils/WolfbearIdGenerator.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>

std::string WolfbearIdGenerator::generateId(const std::string & input){    
    uint64_t hash = WolfbearIdGenerator::getEpochUnixTimestamp();

    for (char c : input) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 1099511628211ULL;
    }

    const char* hexDigits = "0123456789abcdef";
    std::string result(16, '0');
    for (int i = 15; i >= 0; --i) {
        result[i] = hexDigits[hash & 0xF];
        hash >>= 4;
    }
    return result;
}

std::string WolfbearIdGenerator::generateUserId(){
    return "wolfbear.os.user." + WolfbearIdGenerator::generateId("wolfbear.os.user.");
}

std::string WolfbearIdGenerator::generateProfileId(){
    return "wolfbear.os.profile." + WolfbearIdGenerator::generateId("wolfbear.os.profile.");
}

uint64_t WolfbearIdGenerator::getEpochUnixTimestamp(){
    using namespace std::chrono;
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}