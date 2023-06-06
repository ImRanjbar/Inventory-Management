
#ifndef MANUFACTURERS_H
#define MANUFACTURERS_H

#include "seller.h"
#include <algorithm>


class Manufacturers : public Seller
{
public:
    Manufacturers();
    ~Manufacturers();

    void addManufact(Seller* seller);

    bool usernameExistence(const std::string_view username) const;

    bool NINexistence(const std::string_view NIN) const;

    bool MIDexistence(const std::string_view MID) const;

    bool phoneNumberExistence(const std::string_view phoneNumber)const;

    bool checkPassword(std::string_view username, std::string_view password) const;

    const Seller& getSeller(const std::string_view NIN) const;

    const Seller* getManufacturerByUsername(const std::string_view username) const;

    Seller* editSeller(const std::string_view username);

    Seller* editSellerByManuName(const std::string_view manufacturerName);

    const std::vector<Seller*> getManufacturers() const;

    std::vector<Seller*> editManufacturers();

private:
    std::vector<Seller*> m_manufacturers;
};

#endif // MANUFACTURERS_H
