#include <iostream>
#include "responses/UpdatePlayerResponse.h"

UpdatePlayerResponse::UpdatePlayerResponse(){
    std::cout << "Creando objeto UpdatePlayerResponse" << std::endl;
}

UpdatePlayerResponse::~UpdatePlayerResponse(){
    std::cout << "Destruyendo objeto UpdatePlayerResponse" << std::endl;
}

UpdatePlayerResponse* UpdatePlayerResponse::withPlayerProfile(PlayerProfile *pp){
    this->playerProfile = pp;
    return this;
}

PlayerProfile* UpdatePlayerResponse::getPlayerProfile(){
    return this->playerProfile;
}