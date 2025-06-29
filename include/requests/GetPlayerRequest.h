#pragma once

#include "models/PlayerProfile.h"
#include <string>

class GetPlayerRequest {
    private:
        std::string id;
    public:
        GetPlayerRequest();
        ~GetPlayerRequest();

        GetPlayerRequest * setId(const std::string id);
        std::string getId() const;
};