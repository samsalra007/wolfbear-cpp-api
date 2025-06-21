#include <iostream>

#include "players/ProfileManager.h"

#include "requests/CreatePlayerRequest.h"
#include "requests/UpdatePlayerRequest.h"
#include "requests/DeletePlayerRequest.h"

#include "responses/CreatePlayerResponse.h"
#include "responses/UpdatePlayerResponse.h"
#include "responses/DeletePlayerResponse.h"

ProfileManager::ProfileManager(){
    std::cout << "Construyendo el administrador de perfiles" << std:: endl;
}

ProfileManager::~ProfileManager(){
    std::cout << "Destruyendo el administrador de perfiles" << std:: endl;
}

CreatePlayerResponse* ProfileManager::createPlayer(const CreatePlayerRequest *request) const {
    CreatePlayerResponse* response = new CreatePlayerResponse();
    response->withPlayerProfile(request->getPlayerProfile());
    return response;
}

UpdatePlayerResponse* ProfileManager::updatePlayer(const UpdatePlayerRequest *request) const {
    UpdatePlayerResponse* response = new UpdatePlayerResponse();
    response->withPlayerProfile(request->getPlayerProfile());
    return response;
}

DeletePlayerResponse* ProfileManager::deletePlayer(const DeletePlayerRequest *request) const {
    DeletePlayerResponse* response = new DeletePlayerResponse();
    response->withPlayerProfile(request->getPlayerProfile());
    return response;
}

void ProfileManager::getPlayer(){
    std::cout << "Intentando obtener un usuario" << std:: endl;
}
