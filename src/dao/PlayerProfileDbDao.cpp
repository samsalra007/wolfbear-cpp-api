#include "dao/PlayerProfileDbDao.h"

#include <memory>
#include <iostream>
#include <mysql.h>

#include "models/PlayerProfile.h"
#include "wrappers/mysql/MySqlWrapper.h"
#include "wrappers/mysql/MySqlPreparedStatement.h"
#include "wrappers/mysql/MySqlResultBinder.h"

#include "utils/WolfbearIdGenerator.h"

PlayerProfileDbDao::PlayerProfileDbDao(){
    std::cout << "Construyendo PlayerProfileDbDao" << std::endl;
    this->mySqlWrapper = new MySqlWrapper();
    this->mySqlWrapper->connect("localhost", 3306, "wolfbear_user", "welcome", "wolfbear_os");
}

PlayerProfileDbDao::~PlayerProfileDbDao(){
    std::cout << "Destruyendo PlayerProfileDbDao" << std::endl;
    delete this->mySqlWrapper;
}

PlayerProfile * PlayerProfileDbDao::getPlayer(const std::string playerId){
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
                query += "  profiles.profile_id = profiles_latest.profile_id \n";
                query += "  AND profiles.latest_timestamp_date = profiles_latest.latest_timestamp_date \n";
                query += "  AND profiles.player_id = players.player_id";
                query += "  AND players.player_id = ? ;";
    
    auto ps = this->mySqlWrapper->prepareStatement(query);
    ps->setString(playerId);

    std::vector<MySqlResultBinder> results = ps->executeQuery();

    if(results.size() == 0){
        return nullptr;
    }

    MySqlResultBinder result = results.at(0);
    PlayerProfile * player = new PlayerProfile();
    
    player
        ->setId(playerId)
        ->setUsername(result.getString(0))
        ->setNames(result.getString(1))
        ->setLastName(result.getString(2))
        ->setEmail(result.getString(3))
        ->setPrefferedName(result.getString(4))
        ->setProfileImage(result.getString(5));
    
    return player;
}

PlayerProfile * PlayerProfileDbDao::createPlayer(
    std::string username,
    std::string password,
    std::string names,
    std::string lastname,
    std::string email,
    std::string prefferedName,
    std::string profileImage
){
    std::string playerId = WolfbearIdGenerator::generateUserId();
    std::string profileId = WolfbearIdGenerator::generateProfileId();

    std::string query;
    int currentTimestamp = WolfbearIdGenerator::getEpochUnixTimestamp();

    query = "INSERT INTO players (player_id, username, password) VALUES (?, ?, MD5(?));";
    auto ps = this->mySqlWrapper->prepareStatement(query);
    ps->setString(playerId);
    ps->setString(username);
    ps->setString(password);
    ps->executeQuery();

    query  = " INSERT INTO profiles (profile_id, player_id, names, lastname, email, prefferedName, profile_image, latest_timestamp_date) \n";
    query += " VALUES(?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?));";

    ps = this->mySqlWrapper->prepareStatement(query);
    ps->setString(profileId);
    ps->setString(playerId);
    ps->setString(names);
    ps->setString(lastname);
    ps->setString(email);
    ps->setString(prefferedName);
    ps->setString(profileImage);
    ps->setInt(currentTimestamp);
    ps->executeQuery();

    query  = " INSERT INTO profiles_latest (profile_id, latest_timestamp_date) \n";
    query += " VALUES (?, FROM_UNIXTIME(?));";
    ps = this->mySqlWrapper->prepareStatement(query);
    ps->setString(profileId);
    ps->setInt(currentTimestamp);

    PlayerProfile * player = new PlayerProfile();
    
}