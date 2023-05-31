#include "user.h"

void User::setUsername(const std::string_view username) {
    m_username = username;
}

void User::setPassword(const std::string_view password) {
    m_password = password;
}


const std::string& User::getUsername() const{
    return m_username;
}

const std::string& User::getPassword() const{
    return m_password;
}


