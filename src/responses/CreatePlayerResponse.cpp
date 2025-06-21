#include <iostream>
#include "responses/CreatePlayerResponse.h"

CreatePlayerResponse::CreatePlayerResponse(){
    std::cout << "Creando objeto CreatePlayerResponse" << std::endl;
}

CreatePlayerResponse::~CreatePlayerResponse(){
    std::cout << "Destruyendo objeto CreatePlayerResponse" << std::endl;
}

CreatePlayerResponse* CreatePlayerResponse::withPlayerProfile(PlayerProfile *pp){
    this->playerProfile = pp;
    return this;
}

PlayerProfile* CreatePlayerResponse::getPlayerProfile(){
    return this->playerProfile;
}