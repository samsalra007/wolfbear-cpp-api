DROP DATABASE IF EXISTS wolfbear_os;

CREATE DATABASE wolfbear_os;

CREATE USER 'wolfbear_user'@'localhost' IDENTIFIED WITH mysql_native_password BY 'welcome';
GRANT ALL PRIVILEGES ON wolfbear_os.* TO 'wolfbear_user'@'localhost' WITH GRANT OPTION;
FLUSH PRIVILEGES;

USE wolfbear_os;

CREATE TABLE players (
    id INT NOT NULL AUTO_INCREMENT,
    
    username VARCHAR(20),
    password VARCHAR(200),

    PRIMARY KEY (id)
) Engine = INNODB;

CREATE TABLE profiles (
    id INT NOT NULL AUTO_INCREMENT,
    player_id INT NOT NULL,

    creation_date datetime
    modification_date datetime

    names varchar(30),
    lastname varchar(60),

    email varchar(50),

    PRIMARY KEY (id),
    PRIMARY KEY (player_id),

    FOREIGN KEY (player_id) REFERENCES players (id)    
) Engine = INNODB;

CREATE TABLE profiles_latest (
    profile_id INT NOT NULL,
    modification_date datetime NOT NULL
) Engine = INNODB;