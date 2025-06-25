#pragma once

#include <string>
#include <mysql.h>

#include "models/PlayerProfile.h"
#include "wrappers/MySqlWrapper.h"

class PlayerProfileDbDao {
    private:
        MySqlWrapper * mySqlWrapper;
        
    public:
        PlayerProfileDbDao();
        ~PlayerProfileDbDao();

        PlayerProfile * getPlayer(const int id);
};