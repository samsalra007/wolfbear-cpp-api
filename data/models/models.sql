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
) ENGINE = InnoDB;

-- Tabla de perfiles (historial completo)
CREATE TABLE profiles (
    id INT NOT NULL AUTO_INCREMENT,
    player_id INT NOT NULL,

    creation_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    modification_date DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

    names VARCHAR(30),
    lastname VARCHAR(60),
    email VARCHAR(50),

    PRIMARY KEY (id),
    FOREIGN KEY (player_id) REFERENCES players(id)
) ENGINE = InnoDB;

-- Tabla que apunta al perfil más reciente
CREATE TABLE profiles_latest (
    id INT NOT NULL AUTO_INCREMENT,
    profile_id INT NOT NULL,

    modification_date DATETIME NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (profile_id) REFERENCES profiles(id)
) ENGINE = InnoDB;
