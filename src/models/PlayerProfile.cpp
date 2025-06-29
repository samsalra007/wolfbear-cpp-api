#include <iostream>

#include "models/PlayerProfile.h"

PlayerProfile::PlayerProfile(
    const std::string& id,
    const std::string& username,
    const std::string& password,
    const std::string& names,
    const std::string& lastName,
    const std::string& email,
    const std::string& prefferedName,
    const std::string& profileImage)
{
    std::cout << "Construyendo objeto tipo PlayerProfile con parametros" << std::endl;

    this->id = id;
    this->username = username;
    this->password = password;
    this->names = names;
    this->lastName = lastName;
    this->email = email;
    this->prefferedName = prefferedName;
    this->profileImage = profileImage;
}

PlayerProfile::~PlayerProfile(){
    std::cout << "[PlayerProfile] destruyendo objeto con id: " << this->id << std::endl;
}

PlayerProfile* PlayerProfile::setId(const std::string id){
    this->id = id;
    return this;
}

PlayerProfile* PlayerProfile::setUsername(const std::string username){
    this->username = username;
    return this;
}

PlayerProfile* PlayerProfile::setPassword(const std::string password){
    this->password = password;
    return this;
}

PlayerProfile* PlayerProfile::setNames(const std::string names){
    this->names = names;
    return this;
}

PlayerProfile* PlayerProfile::setLastName(const std::string lastName){
    this->lastName = lastName;
    return this;
}

PlayerProfile* PlayerProfile::setPrefferedName(const std::string prefferedName){
    this->prefferedName = prefferedName;
    return this;
}

PlayerProfile* PlayerProfile::setEmail(const std::string email){
    this->email = email;
    return this;
}

PlayerProfile* PlayerProfile::setProfileImage(const std::string profileImage){
    this->profileImage = profileImage;
    return this;
}

std::string PlayerProfile::getId() const {
    return this->id;
}

std::string PlayerProfile::getUsername() const {
    return this->username;
}

std::string PlayerProfile::getNames() const {
    return this->names;
}

std::string PlayerProfile::getLastName() const {
    return this->lastName;
}

std::string PlayerProfile::getPrefferedName() const {
    return this->prefferedName;
}

std::string PlayerProfile::getEmail() const {
    return this->email;
}

std::string PlayerProfile::getProfileImage() const {
    return this->profileImage;
}

void PlayerProfile::logme() {
    std::cout << "[PlayerProfile] Examinando al objeto en la dirección de memoria " << this << std::endl;
    std::cout << "  id: "                 << this->id << std::endl;
    std::cout << "  username: "           << this->username << std::endl;
    std::cout << "  password: ***** "     << std::endl;
    std::cout << "  names: "              << this->names << std::endl;
    std::cout << "  lastName: "           << this->lastName << std::endl;
    std::cout << "  prefferedName: "      << this->prefferedName << std::endl;
    std::cout << "  email: "              << this->email << std::endl;
    std::cout << "  profileImage: "       << this->profileImage << std::endl;
}