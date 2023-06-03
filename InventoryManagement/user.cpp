#include "user.h"

void User::setUsername(const std::string_view username) {
    m_username = username;
}

void User::setPassword(const std::string_view password) {
    m_password = password;
}

void User::setName(const std::string_view name) {
    m_name = name;
}

void User::setLastName(const std::string_view lastName) {
    m_lastName = lastName;
}

void User::setNIN(const std::string_view NIN) {
    m_NIN = NIN;
}

void User::setPhoneNumber(const std::string_view phoneNumber) {
    m_phoneNumber= phoneNumber;
}

const std::string& User::getUsername() const{
    return m_username;
}

const std::string& User::getPassword() const{
    return m_password;
}

const std::string& User::getName() const{
    return m_name;
}

const std::string& User::getLastName() const{
    return m_lastName;
}

const std::string& User::getNIN() const{
    return m_NIN;
}

const std::string& User::getPhoneNumber() const{
    return m_phoneNumber;
}

User::~User(){

}

