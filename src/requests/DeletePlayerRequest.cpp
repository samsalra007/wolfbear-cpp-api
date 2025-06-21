#include <iostream>
#include "requests/DeletePlayerRequest.h"

DeletePlayerRequest::DeletePlayerRequest(){
    std::cout << "Creando objeto DeletePlayerRequest" << std::endl;
}

DeletePlayerRequest::~DeletePlayerRequest(){
    std::cout << "Destruyendo objeto DeletePlayerRequest" << std::endl;
}

DeletePlayerRequest* DeletePlayerRequest::withPlayerProfile(PlayerProfile *pp){
    this->playerProfile = pp;
    return this;
}

PlayerProfile* DeletePlayerRequest::getPlayerProfile() const {
    return this->playerProfile;
}