#pragma once
#include "models/PlayerProfile.h"

class CreatePlayerResponse {
    private:
        PlayerProfile *playerProfile;

    public:
        CreatePlayerResponse();
        ~CreatePlayerResponse();

        CreatePlayerResponse* withPlayerProfile(PlayerProfile* pp);
        PlayerProfile* getPlayerProfile();
};