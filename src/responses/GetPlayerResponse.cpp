#include <iostream>
#include "responses/GetPlayerResponse.h"

GetPlayerResponse::GetPlayerResponse(){
    std::cout << "Creando objeto GetPlayerResponse" << std::endl;
}

GetPlayerResponse::~GetPlayerResponse(){
    std::cout << "Destruyendo objeto GetPlayerResponse" << std::endl;
}

GetPlayerResponse* GetPlayerResponse::setPlayerProfile(PlayerProfile *pp){
    this->playerProfile = pp;
    return this;
}

PlayerProfile* GetPlayerResponse::getPlayerProfile(){
    return this->playerProfile;
}