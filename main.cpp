#include <iostream>
#include "players/ProfileManager.h"

#include "models/PlayerProfile.h"
#include "requests/CreatePlayerRequest.h"
#include "responses/CreatePlayerResponse.h"

int main () {
    std::cout << "Hola, esto esta ejecutandose en C++ " << std:: endl;

    ProfileManager *profileManager = new ProfileManager();

    PlayerProfile *player = new PlayerProfile("wolfbear", "none", "Osito", "Quesito", "cheese@wolfbear.mx", "Cheese Wolfbear");
    CreatePlayerRequest *request = new CreatePlayerRequest();
        request->withPlayerProfile(player);
    
    CreatePlayerResponse *response = profileManager->createPlayer(request);
    player = response->getPlayerProfile();

    player->logme();
    return 0;
}