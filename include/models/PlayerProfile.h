#pragma once
#include <string>

class PlayerProfile {
private:
    std::string username;
    std::string password;
    std::string names;
    std::string lastName;
    std::string email;
    std::string prefferedName;

public:
    PlayerProfile(
        const std::string& username,
        const std::string& password,
        const std::string& names,
        const std::string& lastName,
        const std::string& email,
        const std::string& prefferedName
    );
    ~PlayerProfile();

    PlayerProfile* setUsername(const std::string& username);
    PlayerProfile* setPassword(const std::string& password);
    PlayerProfile* setNames(const std::string& names);
    PlayerProfile* setLastName(const std::string& lastName);
    PlayerProfile* setPrefferedName(const std::string& prefferedName);
    PlayerProfile* setEmail(const std::string& email);

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getNames() const;
    std::string getLastName() const;
    std::string getPrefferedName() const;
    std::string getEmail() const;

    void logme();
};
