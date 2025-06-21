#pragma once
#include "requests/CreatePlayerRequest.h"
#include "responses/CreatePlayerResponse.h"

class ProfileManager {
    public:
        ProfileManager();
        ~ProfileManager();

        CreatePlayerResponse* createPlayer(const CreatePlayerRequest* request) const;
        void updatePlayer();
        void deletePlayer();
        void getPlayer();
};