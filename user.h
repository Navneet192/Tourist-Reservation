#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "tour.h"

class User
{
public:
    void makeReservation();
    void modifyReservation();
    void displayReservations();
    void searchReservation();
    void setPrice(double price);
    double calculateTotalPrice(int numPeople, double pricePerPerson); // Updated declaration
    double getPricePerPerson(const std::string &dcode);

private:
    const std::string userFile = "Reservation.txt";
    double pricePerPerson = 0.0;
    void pack(const Tour &reservation);   
    Tour unpack(const std::string &line);
};

#endif