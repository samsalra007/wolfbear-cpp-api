DROP DATABASE IF EXISTS wolfbear_os;
CREATE DATABASE wolfbear_os;

CREATE USER 'wolfbear_user'@'localhost' IDENTIFIED BY 'welcome';
GRANT ALL PRIVILEGES ON wolfbear_os.* TO 'wolfbear_user'@'localhost';

FLUSH PRIVILEGES;

USE wolfbear_os;

-- Tabla base de jugadores
CREATE TABLE players (
    id INT NOT NULL AUTO_INCREMENT,

    username VARCHAR(20),
    password VARCHAR(200),

    PRIMARY KEY (id)
) ENGINE = InnoDB charset=utf8;

INSERT INTO players (username, password) VALUES ('wolfbear', MD5('welcome'));
INSERT INTO players (username, password) VALUES ('samsalra', MD5('welcome'));

-- Tabla de perfiles
DROP TABLE IF EXISTS profiles;
CREATE TABLE profiles (
    id INT NOT NULL AUTO_INCREMENT,
    player_id INT NOT NULL,

    names VARCHAR(30),
    lastname VARCHAR(60),
    email VARCHAR(50),
    prefferedName VARCHAR(50),
    profile_image VARCHAR(30),

    latest_timestamp_date TIMESTAMP,
    
    PRIMARY KEY(id),
    FOREIGN KEY (player_id) REFERENCES players(id)
) ENGINE = InnoDB charset=utf8;

INSERT INTO profiles (player_id, names, lastname, email, prefferedName, profile_image, latest_timestamp_date) VALUES(1, "Cheese", "Wolfbear", "cheesewolfbear@example.com", "Cheese", "profile.png", FROM_UNIXTIME(1751064237));
INSERT INTO profiles (player_id, names, lastname, email, prefferedName, profile_image, latest_timestamp_date) VALUES(2, "Samuel", "Salazar", "samsalra@example.com", "Samsalra.007", "profile.png", FROM_UNIXTIME(1751064237));

CREATE TABLE profiles_latest (
    profile_id INT NOT NULL,
    latest_timestamp_date TIMESTAMP,

    PRIMARY KEY(profile_id),
    FOREIGN KEY (profile_id) REFERENCES profiles(id)
    
) ENGINE = InnoDB charset=utf8;

INSERT INTO profiles_latest (profile_id, latest_timestamp_date) VALUES (1, FROM_UNIXTIME(1751064237));
INSERT INTO profiles_latest (profile_id, latest_timestamp_date) VALUES (2, FROM_UNIXTIME(1751064237));

SELECT 
    players.username,
    profiles.*
FROM 
    profiles, profiles_latest, players
WHERE
    profiles.id = profiles_latest.profile_id
    AND players.id = profiles_latest.profile_id

-- Tabla de aplicaciones
CREATE TABLE applications (


) ENGINE = InnoDB charset=utf8;
