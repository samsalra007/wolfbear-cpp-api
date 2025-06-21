#include <iostream>
#include "responses/DeletePlayerResponse.h"

DeletePlayerResponse::DeletePlayerResponse(){
    std::cout << "Creando objeto DeletePlayerResponse" << std::endl;
}

DeletePlayerResponse::~DeletePlayerResponse(){
    std::cout << "Destruyendo objeto DeletePlayerResponse" << std::endl;
}

DeletePlayerResponse* DeletePlayerResponse::withPlayerProfile(PlayerProfile *pp){
    this->playerProfile = pp;
    return this;
}

PlayerProfile* DeletePlayerResponse::getPlayerProfile(){
    return this->playerProfile;
}