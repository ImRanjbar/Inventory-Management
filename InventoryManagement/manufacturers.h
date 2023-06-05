
#ifndef MANUFACTURERS_H
#define MANUFACTURERS_H

#include "seller.h"
#include <algorithm>


class Manufacturers : public Seller
{
public:
    Manufacturers();

    void addManufact(Seller* seller);

    bool usernameExistence(const std::string_view username) const;

    bool NINexistence(const std::string_view NIN) const;

    bool MIDexistence(const std::string_view MID) const;

    bool phoneNumberExistence(const std::string_view phoneNumber)const;

    bool checkPassword(std::string_view username, std::string_view password) const;

    const Seller& getSeller(const std::string_view NIN) const;

    const Seller& getSellerByUsername(const std::string_view username) const;

    Seller* editSeller(const std::string_view username);

    const std::vector<Seller*> getManufacturers() const;

    std::vector<Seller*> editManufacturers();

private:
    std::vector<Seller*> m_manufacturers;
};

#endif // MANUFACTURERS_H
