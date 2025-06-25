#include <iostream>
#include "requests/GetPlayerRequest.h"

GetPlayerRequest::GetPlayerRequest(){
    std::cout << "Creando objeto GetPlayerRequest" << std::endl;
}

GetPlayerRequest::~GetPlayerRequest(){
    std::cout << "Destruyendo objeto GetPlayerRequest" << std::endl;
}

GetPlayerRequest* GetPlayerRequest::setId(int id){
    this->id = id;
    return this;
}

int GetPlayerRequest::getId() const {
    return this->id;
}