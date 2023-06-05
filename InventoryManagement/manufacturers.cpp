
#include "manufacturers.h"

Manufacturers::Manufacturers() = default;

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
    if (getSellerByUsername(username).getPassword() == password)
        return true;
    else
        return false;
}

const Seller &Manufacturers::getSellerByUsername(const std::string_view username) const{
    for (Seller* seller: m_manufacturers){
        if (seller->getUsername() == username)
            return *seller;
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

//bool Manufacturers::usernameExistence(const std::string_view username) const
//{

//}

//bool Manufacturers::NINexistence(const std::string_view NIN) const
//{

//}

//bool Manufacturers::MIDexistence(const std::string_view MID) const
//{

//}

//bool Manufacturers::phoneNumberExistence(const std::string_view phoneNumber) const
//{

//}

//const Seller &Manufacturers::getSeller(const std::string_view NIN) const
//{

//}

//Seller &Manufacturers::editSeller(const std::string_view NIN)
//{

//}

//const std::vector<Seller *> Manufacturers::getManufacturers() const
//{

//}

std::vector<Seller *> Manufacturers::editManufacturers(){
    return m_manufacturers;
}
