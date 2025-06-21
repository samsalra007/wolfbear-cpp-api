#pragma once

#include "requests/CreatePlayerRequest.h"
#include "requests/UpdatePlayerRequest.h"
#include "requests/DeletePlayerRequest.h"
#include "requests/GetPlayerRequest.h"

#include "responses/CreatePlayerResponse.h"
#include "responses/UpdatePlayerResponse.h"
#include "responses/DeletePlayerResponse.h"
#include "responses/GetPlayerResponse.h"

class ProfileManager {
    public:
        ProfileManager();
        ~ProfileManager();

        CreatePlayerResponse    *createPlayer(const CreatePlayerRequest* request) const;
        UpdatePlayerResponse    *updatePlayer(const UpdatePlayerRequest* request) const;
        DeletePlayerResponse    *deletePlayer(const DeletePlayerRequest* request) const;
        GetPlayerResponse       *getPlayer(const GetPlayerRequest* request) const;
};