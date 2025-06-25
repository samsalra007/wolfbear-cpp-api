#include <iostream>

#include "players/ProfileManager.h"

#include "requests/CreatePlayerRequest.h"
#include "responses/CreatePlayerResponse.h"

#include "models/PlayerProfile.h"

int main () {
    std::cout << "Hola, esto esta ejecutandose en C++ " << std:: endl;

    ProfileManager * profileManager = new ProfileManager();

    GetPlayerRequest * request = new GetPlayerRequest();
    request->setId(1);
    
    GetPlayerResponse * response = profileManager->getPlayer(request);
    
    PlayerProfile * player = response->getPlayerProfile();
    
    if(player){
        player->logme();
        delete player;
    }
    
    delete request;
    delete response;
    delete profileManager;

    return 0;
}