#pragma once
#include "models/PlayerProfile.h"

class UpdatePlayerRequest {
    private:
        PlayerProfile *playerProfile;

    public:
        UpdatePlayerRequest();
        ~UpdatePlayerRequest();

        UpdatePlayerRequest* withPlayerProfile(PlayerProfile* pp);
        PlayerProfile* getPlayerProfile() const;
};