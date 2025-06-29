#pragma once
#include <string>

class PlayerProfile {
private:
    int id;
    std::string username;
    std::string password;
    std::string names;
    std::string lastName;
    std::string email;
    std::string prefferedName;
    std::string profileImage;

public:
    PlayerProfile() = default;
    PlayerProfile(
        const int id,
        const std::string& username,
        const std::string& password,
        const std::string& names,
        const std::string& lastName,
        const std::string& email,
        const std::string& prefferedName,
        const std::string& profileImage
    );
    ~PlayerProfile();

    PlayerProfile* setId(const int id);
    PlayerProfile* setUsername(const std::string username);
    PlayerProfile* setPassword(const std::string password);
    PlayerProfile* setNames(const std::string names);
    PlayerProfile* setLastName(const std::string lastName);
    PlayerProfile* setEmail(const std::string email);
    PlayerProfile* setPrefferedName(const std::string prefferedName);
    PlayerProfile* setProfileImage(const std::string profileImage);

    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getNames() const;
    std::string getLastName() const;
    std::string getEmail() const;
    std::string getPrefferedName() const;
    std::string getProfileImage() const;

    void logme();
};
