#pragma once
#include "models/PlayerProfile.h"

class UpdatePlayerResponse {
    private:
        PlayerProfile *playerProfile;

    public:
        UpdatePlayerResponse();
        ~UpdatePlayerResponse();

        UpdatePlayerResponse* withPlayerProfile(PlayerProfile* pp);
        PlayerProfile* getPlayerProfile();
};