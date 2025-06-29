DROP DATABASE IF EXISTS wolfbear_os;
CREATE DATABASE wolfbear_os;

CREATE USER 'wolfbear_user'@'localhost' IDENTIFIED BY 'welcome';
GRANT ALL PRIVILEGES ON wolfbear_os.* TO 'wolfbear_user'@'localhost';

FLUSH PRIVILEGES;

USE wolfbear_os;

-- Tabla base de jugadores
CREATE TABLE players (
    player_id varchar(128),

    username VARCHAR(20),
    password VARCHAR(200),

    PRIMARY KEY (player_id)
) ENGINE = InnoDB charset=utf8;

INSERT INTO players (player_id, username, password) VALUES ('wolfbear.os.user.d2031eb7b1ede416', 'wolfbear', MD5('welcome'));

-- Tabla de perfiles
DROP TABLE IF EXISTS profiles;
CREATE TABLE profiles (
    profile_id varchar(128),
    player_id varchar(128),

    names VARCHAR(30),
    lastname VARCHAR(60),
    email VARCHAR(50),
    prefferedName VARCHAR(50),
    profile_image VARCHAR(30),

    latest_timestamp_date TIMESTAMP,
    
    PRIMARY KEY(profile_id),
    FOREIGN KEY (player_id) REFERENCES players(player_id)
) ENGINE = InnoDB charset=utf8;

INSERT INTO profiles (profile_id, player_id, names, lastname, email, prefferedName, profile_image, latest_timestamp_date)
    VALUES('wolfbear.os.profile.cdef84625ba1eb5a', 'wolfbear.os.user.d2031eb7b1ede416', "Cheese", "Wolfbear", "cheesewolfbear@example.com", "Cheese", "profile.png", FROM_UNIXTIME(1751064237));

CREATE TABLE profiles_latest (
    profile_id varchar(128),
    latest_timestamp_date TIMESTAMP,

    PRIMARY KEY(profile_id),
    FOREIGN KEY (profile_id) REFERENCES profiles(profile_id)
    
) ENGINE = InnoDB charset=utf8;

INSERT INTO profiles_latest (profile_id, latest_timestamp_date)
    VALUES ('wolfbear.os.profile.cdef84625ba1eb5a', FROM_UNIXTIME(1751064237));

SELECT 
    players.username,
    profiles.*
FROM 
    profiles, profiles_latest, players
WHERE
    profiles.profile_id = profiles_latest.profile_id
    AND profiles.latest_timestamp_date = profiles_latest.latest_timestamp_date
    AND players.player_id = profiles.player_id;

-- Tabla de aplicaciones
CREATE TABLE applications (


) ENGINE = InnoDB charset=utf8;
