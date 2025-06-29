#include <iostream>
#include <list>
#include <memory>

#include "players/ProfileManager.h"

#include "requests/CreatePlayerRequest.h"
#include "requests/UpdatePlayerRequest.h"
#include "requests/DeletePlayerRequest.h"

#include "responses/CreatePlayerResponse.h"
#include "responses/UpdatePlayerResponse.h"
#include "responses/DeletePlayerResponse.h"

#include <mysql.h>
#include "dao/PlayerProfileDbDao.h"

ProfileManager::ProfileManager(){
    std::cout << "Construyendo el objeto ProfileManager" << std:: endl;
    this->playerProfileDbDao = new PlayerProfileDbDao();
}

ProfileManager::~ProfileManager(){
    std::cout << "Destruyendo el objeto ProfileManager" << std:: endl;
    delete this->playerProfileDbDao;
}

CreatePlayerResponse* ProfileManager::createPlayer(const CreatePlayerRequest *request) {
    CreatePlayerResponse *response = new CreatePlayerResponse();
    PlayerProfile *playerProfile = request->getPlayerProfile();

    response->withPlayerProfile(request->getPlayerProfile());
    return response;
}

UpdatePlayerResponse* ProfileManager::updatePlayer(const UpdatePlayerRequest *request) const {
    UpdatePlayerResponse *response = new UpdatePlayerResponse();
    response->withPlayerProfile(request->getPlayerProfile());
    return response;
}

DeletePlayerResponse* ProfileManager::deletePlayer(const DeletePlayerRequest *request) const {
    DeletePlayerResponse *response = new DeletePlayerResponse();
    response->withPlayerProfile(request->getPlayerProfile());
    return response;
}

std::unique_ptr<GetPlayerResponse> ProfileManager::getPlayer(std::unique_ptr<GetPlayerRequest> & request){
    auto response = std::make_unique<GetPlayerResponse>();
    
    PlayerProfile * playerProfile = this->playerProfileDbDao
        ->getPlayer(request->getId());

    response->setPlayerProfile(playerProfile);

    return response;
}
