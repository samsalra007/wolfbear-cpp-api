#pragma once
#include "models/PlayerProfile.h"

class GetPlayerResponse {
    private:
        PlayerProfile *playerProfile;

    public:
        GetPlayerResponse();
        ~GetPlayerResponse();

        GetPlayerResponse* setPlayerProfile(PlayerProfile* pp);
        PlayerProfile* getPlayerProfile();
};