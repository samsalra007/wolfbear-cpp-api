#pragma once
#include "models/PlayerProfile.h"

class DeletePlayerResponse {
    private:
        PlayerProfile *playerProfile;

    public:
        DeletePlayerResponse();
        ~DeletePlayerResponse();

        DeletePlayerResponse* withPlayerProfile(PlayerProfile* pp);
        PlayerProfile* getPlayerProfile();
};