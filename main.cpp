#include "admin.h"
#include "user.h"
#include <iostream>
using namespace std;

int main()
{
    Admin admin;
    User user;

    while (true)
    {
        cout << "Welcome to the Tourist Reservation System\n";
        cout << "1. Admin\n2. User\n3. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Admin Menu:\n1. Add Trip\n2. View Trips\n3. Modify Trip\nEnter your choice: ";
            int adminChoice;
            cin >> adminChoice;
            if (adminChoice == 1)
                admin.addTrip();
            else if (adminChoice == 2)
                admin.displayTrips();
            else if (adminChoice == 3)
                admin.modifyTrip();
        }
        else if (choice == 2)
        {
            cout << "User Menu:\n1. Make Reservation\n2. View Reservations\n3. Search Reservation\n4. Modify Reservation\nEnter your choice: ";
            int userChoice;
            cin >> userChoice;
            if (userChoice == 1)
                user.makeReservation();
            else if (userChoice == 2)
                user.displayReservations();
            else if (userChoice == 3)
                user.searchReservation();
            else if (userChoice == 4)
                user.modifyReservation();
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}