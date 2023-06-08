
#include "manufacturers.h"

Manufacturers::Manufacturers() = default;

Manufacturers::~Manufacturers(){
    for (Seller* seller : m_manufacturers){
        delete seller;
    }
}

void Manufacturers::addManufact(Seller* seller){
    m_manufacturers.push_back(seller);
}

bool Manufacturers::usernameExistence(const std::string_view username) const{
    bool doesExist = std::ranges::any_of(m_manufacturers, [username](const Seller* seller){
        return seller->getUsername() == username;
    });

    return doesExist;
}

bool Manufacturers::checkPassword(std::string_view username, std::string_view password) const{
    if (getManufacturerByUsername(username)->getPassword() == password)
        return true;
    else
        return false;
}

const Seller &Manufacturers::getSellerByMID(const std::string_view MID) const{
    for (const Seller* seller : m_manufacturers){
        if (seller->getMID() == MID)
            return *seller;
    }
    throw std::runtime_error("Seller not found.");
}

const Seller* Manufacturers::getManufacturerByUsername(const std::string_view username) const{
    for (Seller* seller: m_manufacturers){
        if (seller->getUsername() == username)
            return seller;
    }
    throw std::runtime_error("Seller not found.");
}

Seller* Manufacturers::editSeller(const std::string_view username){
    for (Seller* seller: m_manufacturers){
        if (seller->getUsername() == username)
            return seller;
    }
    throw std::runtime_error("Seller not found.");

}

Seller *Manufacturers::editSellerByManuName(const std::string_view manufacturerName){
    for (Seller* seller: m_manufacturers){
        if (seller->getManufactureName() == manufacturerName)
            return seller;
    }
    throw std::runtime_error("Seller not found.");
}

const std::vector<Seller *> Manufacturers::getManufacturers() const{
    return m_manufacturers;
}

std::vector<Seller *> Manufacturers::editManufacturers(){
    return m_manufacturers;
}
