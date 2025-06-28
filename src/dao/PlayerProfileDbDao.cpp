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

    auto result = ps->executeQuery();
    
    return NULL;
}