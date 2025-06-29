#pragma once

#include <string>
#include <mysql.h>

#include "models/PlayerProfile.h"
#include "wrappers/mysql/MySqlWrapper.h"

class PlayerProfileDbDao {
    private:
        MySqlWrapper * mySqlWrapper;
        
    public:
        PlayerProfileDbDao();
        ~PlayerProfileDbDao();

        PlayerProfile * getPlayer(const std::string playerId);
        PlayerProfile * createPlayer(
            std::string username,
            std::string password,
            std::string names,
            std::string lastname,
            std::string email,
            std::string prefferedName,
            std::string profileImage
        );
};