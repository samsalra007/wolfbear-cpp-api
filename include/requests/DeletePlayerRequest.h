#pragma once
#include "models/PlayerProfile.h"

class DeletePlayerRequest {
    private:
        PlayerProfile *playerProfile;

    public:
        DeletePlayerRequest();
        ~DeletePlayerRequest();

        DeletePlayerRequest* withPlayerProfile(PlayerProfile* pp);
        PlayerProfile* getPlayerProfile() const;
};