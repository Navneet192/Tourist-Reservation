#include "admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void Admin::saveTrip(const Tour &trip)
{
    ofstream fp(adminFile, ios::app);
    if (!fp)
    {
        cerr << "Cannot open file " << adminFile << endl;
        return;
    }
    fp << trip.ad_code << "|" << trip.ad_place << "|" << trip.ad_country << "|"
       << trip.ad_days << "|" << trip.ad_prices << endl;
}

Tour Admin::unpackTrip(const string &line)
{
    Tour trip;
    stringstream ss(line);
    getline(ss, trip.ad_code, '|');
    getline(ss, trip.ad_place, '|');
    getline(ss, trip.ad_country, '|');
    getline(ss, trip.ad_days, '|');
    getline(ss, trip.ad_prices, '|');
    return trip;
}

void Admin::addTrip()
{
    Tour trip;
    cout << "Enter the Destination Code\nD-";
    cin >> trip.ad_code;
    cout << "Enter the Destination Place\n";
    cin >> trip.ad_place;
    cout << "Enter the Country of the Destination\n";
    cin >> trip.ad_country;
    cout << "Enter the Number of Days of the Trip\n";
    cin >> trip.ad_days;
    cout << "Enter the Cost of the Trip\n";
    cin >> trip.ad_prices;
    saveTrip(trip);
}

void Admin::displayTrips()
{
    ifstream fp(adminFile);
    if (!fp)
    {
        cerr << "Cannot open file " << adminFile << endl;
        return;
    }

    string line;
    cout << "-------------------------------------------------------------------------------------------------\n";
    cout << "Sr No.\t\tDEST. CODE\tPLACE\t\tCOUNTRY\t\tDAYS\t\tPRICES\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    int count = 1;
    while (getline(fp, line))
    {
        Tour trip = unpackTrip(line);
        cout << count++ << "\t\t" << trip.ad_code << "\t\t" << trip.ad_place << "\t\t"
             << trip.ad_country << "\t\t" << trip.ad_days << "\t\t" << trip.ad_prices << endl;
    }
}

void Admin::modifyTrip()
{
    ifstream fp(adminFile);
    if (!fp)
    {
        cerr << "Cannot open file " << adminFile << endl;
        return;
    }

    string ad_code;
    cout << "\nEnter the Destination Code to be Modified: ";
    cin >> ad_code;

    vector<Tour> trips;
    string line;
    while (getline(fp, line))
    {
        trips.push_back(unpackTrip(line));
    }
    fp.close();

    auto it = find_if(trips.begin(), trips.end(), [&](const Tour &t)
                      { return t.ad_code == ad_code; });

    if (it != trips.end())
    {
        cout << "Updating trip: " << it->ad_code << " " << it->ad_place << endl;
        cout << "Enter new place: ";
        cin >> it->ad_place;
        cout << "Enter new days: ";
        cin >> it->ad_days;
        cout << "Enter new price: ";
        cin >> it->ad_prices;

        ofstream out(adminFile, ios::trunc);
        for (const auto &trip : trips)
        {
            saveTrip(trip);
        }
    }
    else
    {
        cout << "Trip not found.\n";
    }
}