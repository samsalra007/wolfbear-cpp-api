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

ProfileManager::ProfileManager(){
    std::cout << "Construyendo el objeto ProfileManager" << std:: endl;
}

ProfileManager::~ProfileManager(){
    std::cout << "Destruyendo el objeto ProfileManager" << std:: endl;
}

CreatePlayerResponse* ProfileManager::createPlayer(const CreatePlayerRequest *request) {
    CreatePlayerResponse *response = new CreatePlayerResponse();
    PlayerProfile *playerProfile = request->getPlayerProfile();

    this->players.push_front(std::unique_ptr<PlayerProfile>(playerProfile));

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

GetPlayerResponse* ProfileManager::getPlayer(const GetPlayerRequest*request){
    GetPlayerResponse *response = new GetPlayerResponse();
    PlayerProfile *profile = new PlayerProfile();

    profile
        ->setId(9999)
        ->setEmail("test@test.com")
        ->setNames("Testing names")
        ->setPrefferedName("Testing preffered name");

    this->players.push_front(std::unique_ptr<PlayerProfile>(profile));

    response->withPlayerProfile(profile);
    return response;
}
