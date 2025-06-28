#include "dao/PlayerProfileDbDao.h"

#include <memory>
#include <iostream>
#include <mysql.h>

#include "models/PlayerProfile.h"
#include "wrappers/mysql/MySqlWrapper.h"
#include "wrappers/mysql/MySqlBindWrapper.h"
#include "wrappers/mysql/MySqlPreparedStatement.h"

PlayerProfileDbDao::PlayerProfileDbDao(){
    std::cout << "Construyendo PlayerProfileDbDao" << std::endl;
    this->mySqlWrapper = new MySqlWrapper();
}

PlayerProfileDbDao::~PlayerProfileDbDao(){
    std::cout << "Destruyendo PlayerProfileDbDao" << std::endl;
    delete this->mySqlWrapper;
}

PlayerProfile * PlayerProfileDbDao::getPlayer(const int id){
    std::cout << "Ejecutando PlayerProfileDbDao.getPlayer()" << std::endl;

    std::string query = "";

    this->mySqlWrapper->connect();

    MYSQL * connection = this->mySqlWrapper->getConnection();

    query += " SELECT \n";
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
    
    auto mySqlPreparedStatement = std::make_unique<MySqlPreparedStatement>();
    
    MYSQL_STMT * preparedStatement = mySqlWrapper->createPreparedStatement();
    
    auto mySqlBindWrapper = std::make_unique<MySqlBindWrapper>();

    mySqlBindWrapper->bindInt(id);

    mySqlWrapper->statementPrepare(preparedStatement, query);
    mySqlWrapper->statementBindParams(preparedStatement, mySqlBindWrapper->getBindArray());
    
    std::cout << "Intentando ejecutar consulta" << std::endl;
    std::cout << query << std::endl;

    if(mysql_stmt_execute(preparedStatement)){
        std::cout << "Error al ejecutar la consulta" << std::endl;
        return NULL;
    } else {
        std::cout << "Consulta realizada exitosamente" << std::endl;
    }

    mySqlBindWrapper->clear();
    
    MYSQL_BIND result [6];
    char username[20], names[30], lastname[60], email[50], prefferedName[50], profileImage[30];
    unsigned long lengths[6];

    my_bool is_null[6];

    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = username;
    result[0].buffer_length = sizeof(username);
    result[0].length = &lengths[0];
    result[0].is_null = &is_null[0];

    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = names;
    result[1].buffer_length = sizeof(names);
    result[1].length = &lengths[1];
    result[1].is_null = &is_null[1];

    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = lastname;
    result[2].buffer_length = sizeof(lastname);
    result[2].length = &lengths[2];
    result[2].is_null = &is_null[2];

    result[3].buffer_type = MYSQL_TYPE_STRING;
    result[3].buffer = email;
    result[3].buffer_length = sizeof(email);
    result[3].length = &lengths[3];
    result[3].is_null = &is_null[3];

    result[4].buffer_type = MYSQL_TYPE_STRING;
    result[4].buffer = prefferedName;
    result[4].buffer_length = sizeof(prefferedName);
    result[4].length = &lengths[4];
    result[4].is_null = &is_null[4];

    result[5].buffer_type = MYSQL_TYPE_STRING;
    result[5].buffer = profileImage;
    result[5].buffer_length = sizeof(profileImage);
    result[5].length = &lengths[5];
    result[5].is_null = &is_null[5];

    mysql_stmt_bind_result(preparedStatement, result);
    
    PlayerProfile * playerProfile;

    if (mysql_stmt_fetch(preparedStatement) == 0) {
        playerProfile = new PlayerProfile();
        playerProfile
            ->setId(id)
            ->setUsername(username)
            ->setNames(names)
            ->setLastName(lastname)
            ->setPrefferedName(prefferedName)
            ->setEmail(email)
            ->setProfileImage(profileImage);
        
    } else {
        std::cout << "No existen datos para bindear ya que la consulta es vacia" << std::endl;
    }
    
    mysql_stmt_close(preparedStatement);
    this->mySqlWrapper->disconnect();    
    return playerProfile;
}