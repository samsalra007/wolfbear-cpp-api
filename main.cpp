#include <iostream>

#include "players/ProfileManager.h"

#include "requests/CreatePlayerRequest.h"
#include "responses/CreatePlayerResponse.h"

#include "models/PlayerProfile.h"

int main () {
    std::cout << "Hola, esto esta ejecutandose en C++ " << std:: endl;

    ProfileManager * profileManager = new ProfileManager();
    const int playerId = 1;
    GetPlayerRequest * request = new GetPlayerRequest();
    request->setId(playerId);
    
    GetPlayerResponse * response = profileManager->getPlayer(request);
    
    PlayerProfile * player = response->getPlayerProfile();
    
    if(player){
        std::cout << "Se encontró al jugador con id:'" << playerId << "'" << std::endl;
        player->logme();
        delete player;
    } else {
        std::cout << "No se encontró el jugador con id:'" << playerId << "'" << std::endl;
    }
    
    delete request;
    delete response;
    delete profileManager;

    return 0;
}