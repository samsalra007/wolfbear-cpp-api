#pragma once
#include "models/PlayerProfile.h"

class GetPlayerRequest {
    private:
        int id;
    public:
        GetPlayerRequest();
        ~GetPlayerRequest();

        GetPlayerRequest* withId(int id);
        int getId() const;
};