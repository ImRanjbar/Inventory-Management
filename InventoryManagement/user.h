
#ifndef USER_H
#define USER_H

#include <iostream>
#include <algorithm>
#include <vector>

class User {

public:
    ~User();
    void setUsername(const std::string_view username);
    void setPassword(const std::string_view password);
    void setName(const std::string_view name);
    void setLastName(const std::string_view lastName);
    void setNIN(const std::string_view NIN);
    void setPhoneNumber(const std::string_view phoneNumber);

    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::string& getName() const;
    const std::string& getLastName() const;
    const std::string& getNIN() const;
    const std::string& getPhoneNumber() const;

private:
    std::string m_username;
    std::string m_password;
    std::string m_name;
    std::string m_lastName;
    std::string m_NIN;
    std::string m_phoneNumber;
};

#endif // USER_H
