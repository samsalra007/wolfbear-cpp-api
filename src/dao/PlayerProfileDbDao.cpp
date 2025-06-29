#include "dao/PlayerProfileDbDao.h"

#include <memory>
#include <iostream>
#include <mysql.h>

#include "models/PlayerProfile.h"
#include "wrappers/mysql/MySqlWrapper.h"
#include "wrappers/mysql/MySqlPreparedStatement.h"
#include "wrappers/mysql/MySqlResultBinder.h"

PlayerProfileDbDao::PlayerProfileDbDao(){
    std::cout << "Construyendo PlayerProfileDbDao" << std::endl;
    this->mySqlWrapper = new MySqlWrapper();
    this->mySqlWrapper->connect("localhost", 3306, "wolfbear_user", "welcome", "wolfbear_os");
}

PlayerProfileDbDao::~PlayerProfileDbDao(){
    std::cout << "Destruyendo PlayerProfileDbDao" << std::endl;
    delete this->mySqlWrapper;
}

PlayerProfile * PlayerProfileDbDao::getPlayer(const int id){
    std::cout << "Ejecutando PlayerProfileDbDao.getPlayer()" << std::endl;

    std::string query  = " SELECT \n";
                query += "  players.username, \n";
                query += "  profiles.names, \n";
                query += "  profiles.lastname, \n";
                query += "  profiles.email, \n";
                query += "  profiles.prefferedName, \n";
                query += "  profiles.profile_image \n";

                query += " FROM \n";
                query += "  profiles, profiles_latest, players \n";

                query += " WHERE \n";
                query += "  profiles.id = profiles_latest.profile_id \n";
                query += "  AND players.id = profiles_latest.profile_id \n";
                query += "  AND players.id = ? ;";
    
    auto ps = this->mySqlWrapper->prepareStatement(query);
    ps->setInt(id);

    std::vector<MySqlResultBinder> results = ps->executeQuery();

    if(results.size() == 0){
        return nullptr;
    }

    MySqlResultBinder result = results.at(0);
    PlayerProfile * player = new PlayerProfile();
    
    player
        ->setId(id)
        ->setUsername(result.getString(0))
        ->setNames(result.getString(1))
        ->setLastName(result.getString(2))
        ->setEmail(result.getString(3))
        ->setPrefferedName(result.getString(4))
        ->setProfileImage(result.getString(5));
    
    return player;
}