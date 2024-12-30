#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include "tour.h"

class Admin
{
public:
    void addTrip();
    void modifyTrip();
    void displayTrips();

private:
    const std::string adminFile = "Trip.txt";
    void saveTrip(const Tour &trip);
    Tour unpackTrip(const std::string &line);
};

#endif // ADMIN_H