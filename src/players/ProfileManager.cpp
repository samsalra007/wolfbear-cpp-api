#include <iostream>

#include "players/ProfileManager.h"
#include "requests/CreatePlayerRequest.h"
#include "responses/CreatePlayerResponse.h"

ProfileManager::ProfileManager(){
    std::cout << "Construyendo el administrador de perfiles" << std:: endl;
}

ProfileManager::~ProfileManager(){
    std::cout << "Destruyendo el administrador de perfiles" << std:: endl;
}

CreatePlayerResponse* ProfileManager::createPlayer(const CreatePlayerRequest* request) const {
    CreatePlayerResponse* response = new CreatePlayerResponse();
    response->withPlayerProfile(request->getPlayerProfile());
    return response;
}

void ProfileManager::getPlayer(){
    std::cout << "Intentando obtener un usuario" << std:: endl;
}

void ProfileManager::updatePlayer(){
    std::cout << "Intentando actualizar un usuario" << std:: endl;
}

void ProfileManager::deletePlayer(){
    std::cout << "Intentando eliminar un usuario" << std:: endl;
}
