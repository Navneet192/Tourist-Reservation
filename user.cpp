#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

double User::getPricePerPerson(const string &dcode)
{
    ifstream inFile("Trip.txt");
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string code, place, country, days, price;
        getline(ss, code, '|');
        getline(ss, place, '|');
        getline(ss, country, '|');
        getline(ss, days, '|');
        getline(ss, price, '|');
        if (code == dcode)
        {
            return stod(price);
        }
    }
    inFile.close();
    return 0.0;
}

void User::setPrice(double price)
{
    pricePerPerson = price;
}

void User::makeReservation()
{
    Tour reservation;
    cout << "Enter your name: " << endl;
    cin >> reservation.us_name;
    cout << "Enter your contact number: " << endl;
    cin >> reservation.us_phone;
    cout << "Enter the number of people: " << endl;
    cin >> reservation.us_people;
    cout << "Enter the destination code (D-): " << endl;
    cin >> reservation.us_dcode;
    cout << "Enter your date of journey (DD/MM/YY): " << endl;
    cin >> reservation.us_date;

    int totalPeople = stoi(reservation.us_people);
    vector<string> names(totalPeople);
    cout << "Enter the names of all " << totalPeople << " people:" << endl;
    for (int i = 0; i < totalPeople; ++i)
    {
        cout << "Name " << (i + 1) << ": ";
        cin >> names[i];
    }
    stringstream ss;
    for (int i = 1; i < totalPeople; ++i)
    {
        if (i != 0)
            ss << ", ";
        ss << names[i];
    }
    reservation.us_name = ss.str();
    pack(reservation);

    int numPeople = stoi(reservation.us_people);
    double pricePerPerson = getPricePerPerson(reservation.us_dcode);
    setPrice(pricePerPerson);
    double totalPrice = calculateTotalPrice(numPeople, pricePerPerson);
    cout << "Total price for " << numPeople << " people is: ₹" << totalPrice << endl;
    cout << "Enter status (Confirm/Cancel): ";
    cin >> reservation.us_status;
}

double User::calculateTotalPrice(int numPeople, double pricePerPerson)
{
    return numPeople * pricePerPerson;
}

void User::pack(const Tour &reservation)
{
    ofstream fp(userFile, ios::app);
    if (!fp)
    {
        cerr << "Cannot open file " << userFile << endl;
        return;
    }
    fp << reservation.us_name << "|" << reservation.us_phone << "|" << reservation.us_people << "|"
       << reservation.us_dcode << "|" << reservation.us_date << "|" << reservation.us_status << endl;
}

Tour User::unpack(const string &line)
{
    Tour reservation;
    stringstream ss(line);
    getline(ss, reservation.us_name, '|');
    getline(ss, reservation.us_phone, '|');
    getline(ss, reservation.us_people, '|');
    getline(ss, reservation.us_dcode, '|');
    getline(ss, reservation.us_date, '|');
    getline(ss, reservation.us_status, '|');
    return reservation;
}

void User::modifyReservation()
{
    string reservationID;
    cout << "Enter Reservation ID (name) to modify: ";
    cin >> reservationID;

    ifstream inFile(userFile);
    vector<string> reservations;
    string line;
    while (getline(inFile, line))
    {
        reservations.push_back(line);
    }
    inFile.close();

    bool found = false;
    for (auto &reservation : reservations)
    {
        if (reservation.find(reservationID) != string::npos)
        {
            cout << "Current Reservation: " << reservation << endl;
            cout << "Enter new details: ";
            cin.ignore();
            getline(cin, reservation);
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Reservation ID not found." << endl;
        return;
    }

    ofstream outFile(userFile);
    for (const auto &reservation : reservations)
    {
        outFile << reservation << endl;
    }
    outFile.close();
}

void User::searchReservation()
{
    string reservationID;
    cout << "Enter Reservation ID (name) to search: ";
    cin >> reservationID;

    ifstream inFile(userFile);
    string line;
    bool found = false;
    while (getline(inFile, line))
    {
        if (line.find(reservationID) != string::npos)
        {
            cout << "Reservation found: " << line << endl;
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found)
    {
        cout << "Reservation ID not found." << endl;
    }
}

void User::displayReservations()
{
    string userPhone;
    cout << "Enter your contact number to display your reservations: ";
    cin >> userPhone;

    ifstream inFile(userFile);
    string line;
    bool found = false;
    while (getline(inFile, line))
    {
        Tour reservation = unpack(line);
        if (reservation.us_phone == userPhone)
        {
            cout << line << endl;
            found = true;
        }
    }
    inFile.close();

    if (!found)
    {
        cout << "No reservations found for contact number: " << userPhone << endl;
    }
}