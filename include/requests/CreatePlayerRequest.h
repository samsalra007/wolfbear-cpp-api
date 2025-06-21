#pragma once
#include "models/PlayerProfile.h"

class CreatePlayerRequest {
    private:
        PlayerProfile *playerProfile;

    public:
        CreatePlayerRequest();
        ~CreatePlayerRequest();

        CreatePlayerRequest* withPlayerProfile(PlayerProfile* pp);
        PlayerProfile* getPlayerProfile() const;
};