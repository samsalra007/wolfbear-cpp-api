#include <iostream>

#include "players/ProfileManager.h"

#include "requests/CreatePlayerRequest.h"
#include "responses/CreatePlayerResponse.h"

#include "models/PlayerProfile.h"

int main () {
    std::cout << "Hola, esto esta ejecutandose en C++ " << std:: endl;
    std::string playerId = "wolfbear.os.user.d2031eb7b1ede416";

    auto profileManager     = std::make_unique<ProfileManager>();
    auto request            = std::make_unique<GetPlayerRequest>();

    request->setId(playerId);
    
    auto response = profileManager->getPlayer(request);
    
    PlayerProfile * player = response->getPlayerProfile();
    
    if(player){
        std::cout << "Se encontró al jugador con id:'" << playerId << "'" << std::endl;
        player->logme();
        delete player;
    } else {
        std::cout << "No se encontró el jugador con id:'" << playerId << "'" << std::endl;
    }

    return 0;
}