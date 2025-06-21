#include <iostream>
#include "requests/UpdatePlayerRequest.h"

UpdatePlayerRequest::UpdatePlayerRequest(){
    std::cout << "Creando objeto UpdatePlayerRequest" << std::endl;
}

UpdatePlayerRequest::~UpdatePlayerRequest(){
    std::cout << "Destruyendo objeto UpdatePlayerRequest" << std::endl;
}

UpdatePlayerRequest* UpdatePlayerRequest::withPlayerProfile(PlayerProfile *pp){
    this->playerProfile = pp;
    return this;
}

PlayerProfile* UpdatePlayerRequest::getPlayerProfile() const {
    return this->playerProfile;
}