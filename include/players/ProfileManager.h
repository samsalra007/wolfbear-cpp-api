#pragma once

#include "requests/CreatePlayerRequest.h"
#include "requests/UpdatePlayerRequest.h"
#include "requests/DeletePlayerRequest.h"

#include "responses/CreatePlayerResponse.h"
#include "responses/UpdatePlayerResponse.h"
#include "responses/DeletePlayerResponse.h"

class ProfileManager {
    public:
        ProfileManager();
        ~ProfileManager();

        CreatePlayerResponse *createPlayer(const CreatePlayerRequest* request) const;
        UpdatePlayerResponse *updatePlayer(const UpdatePlayerRequest* request) const;
        DeletePlayerResponse *deletePlayer(const DeletePlayerRequest* request) const;
        void getPlayer();
};