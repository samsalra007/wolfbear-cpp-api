#include <iostream>
#include "requests/CreatePlayerRequest.h"

CreatePlayerRequest::CreatePlayerRequest(){
    std::cout << "Creando objeto CreatePlayerRequest" << std::endl;
}

CreatePlayerRequest::~CreatePlayerRequest(){
    std::cout << "Destruyendo objeto CreatePlayerRequest" << std::endl;
}

CreatePlayerRequest* CreatePlayerRequest::withPlayerProfile(PlayerProfile *pp){
    this->playerProfile = pp;
    return this;
}

PlayerProfile* CreatePlayerRequest::getPlayerProfile() const {
    return this->playerProfile;
}