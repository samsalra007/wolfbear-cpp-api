#include <iostream>
#include "requests/GetPlayerRequest.h"

GetPlayerRequest::GetPlayerRequest(){
    std::cout << "Creando objeto GetPlayerRequest" << std::endl;
}

GetPlayerRequest::~GetPlayerRequest(){
    std::cout << "Destruyendo objeto GetPlayerRequest" << std::endl;
}

GetPlayerRequest* GetPlayerRequest::setId(const std::string id){
    this->id = id;
    return this;
}

std::string GetPlayerRequest::getId() const {
    return this->id;
}