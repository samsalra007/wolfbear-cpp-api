#include "dao/PlayerProfileDbDao.h"

#include <iostream>
#include <mysql.h>

#include "models/PlayerProfile.h"
#include "wrappers/MySqlWrapper.h"

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

    query += "SELECT \n";
    query += "  pla.username, pro.names, pro.lastname, pro.profile_image \n";

    query += "FROM \n";
    query += "  profiles pro \n";

    query += "INNER JOIN profiles_latest pro_l ON pro_l.profile_id = pro.id \n";
    query += "INNER JOIN players pla ON pla.id = pro.player_id \n";

    query += "WHERE pla.id = ?";

    MYSQL_STMT * preparedStatement = mysql_stmt_init(connection);
    MYSQL_BIND bindings [1];

    mysql_stmt_prepare(preparedStatement, query.c_str(), query.length());

    memset(bindings, 0, sizeof(bindings));
    bindings[0].buffer_type = MYSQL_TYPE_LONG;
    bindings[0].buffer = (void *) &id;

    mysql_stmt_bind_param(preparedStatement, bindings);
    
    std::cout << "Intentando ejecutar consulta" << std::endl;
    std::cout << query << std::endl;

    if(mysql_stmt_execute(preparedStatement)){
        std::cout << "Error al ejecutar la consulta" << std::endl;
        return NULL;
    } else {
        std::cout << "Consulta realizada exitosamente" << std::endl;
    }
    
    MYSQL_BIND result [4];
    char username[20], names[30], lastname[60], profileImage [50];
    unsigned long lengths[4];
    my_bool is_null[4];

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
    result[3].buffer = profileImage;
    result[3].buffer_length = sizeof(profileImage);
    result[3].length = &lengths[3];
    result[3].is_null = &is_null[3];

     mysql_stmt_bind_result(preparedStatement, result);
    
    PlayerProfile * playerProfile = new PlayerProfile();

    if (mysql_stmt_fetch(preparedStatement) == 0) {
        PlayerProfile *player = new PlayerProfile();
        player->setId(id);
        player->setUsername(username);
        player->setNames(names);
        player->setLastName(lastname);

        mysql_stmt_close(preparedStatement);
        return player;
    } else {
        std::cout << "No existen datos para bindear ya que la consulta es vacia" << std::endl;
    }

    this->mySqlWrapper->disconnect();
    
    return NULL;
}