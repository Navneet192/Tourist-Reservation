#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string adminf = "Trip.txt";
const string userf = "Reservation.txt";

struct Tour
{
    string ad_place, ad_code, ad_country, ad_days, ad_prices;
    string us_phone, us_name, us_people, us_date, us_status, us_dcode;
};

class Tourist
{
public:
    void ad_pack(const Tour &r);
    Tour ad_unpack(const string &line);
    void ad_writedata();
    void ad_display();
    void ad_modify();
    void us_pack(const Tour &r);
    Tour us_unpack(const string &line);
    void us_writedata();
    void us_display();
    void us_search();
    void us_modify();
};

void Tourist::ad_pack(const Tour &r)
{
    ofstream fp(adminf, ios::app);
    if (!fp)
    {
        cerr << "Cannot open file " << adminf << endl;
        return;
    }
    fp << r.ad_code << "|" << r.ad_place << "|" << r.ad_country << "|"
       << r.ad_days << "|" << r.ad_prices << endl;
}

Tour Tourist::ad_unpack(const string &line)
{
    Tour r;
    stringstream ss(line);
    getline(ss, r.ad_code, '|');
    getline(ss, r.ad_place, '|');
    getline(ss, r.ad_country, '|');
    getline(ss, r.ad_days, '|');
    getline(ss, r.ad_prices, '|');
    return r;
}

void Tourist::ad_writedata()
{
    Tour s;
    cout << "Enter the Destination Code\nD-";
    cin >> s.ad_code;
    cout << "Enter the Destination Place\n";
    cin >> s.ad_place;
    cout << "Enter the Country of the Destination\n";
    cin >> s.ad_country;
    cout << "Enter the Number of days of the Trip\n";
    cin >> s.ad_days;
    cout << "Enter the Cost of the trip\n";
    cin >> s.ad_prices;
    ad_pack(s);
}

void Tourist::ad_display()
{
    ifstream fp(adminf);
    if (!fp)
    {
        cerr << "Cannot open file " << adminf << endl;
        return;
    }

    string line;
    cout << "-------------------------------------------------------------------------------------------------\n";
    cout << "Sr No.\t\tDEST. CODE\tPLACE\t\tCOUNTRY\t\tDAYS\t\tPRICES\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    int c = 1;
    while (getline(fp, line))
    {
        Tour r = ad_unpack(line);
        cout << c++ << "\t\t" << r.ad_code << "\t\t" << r.ad_place << "\t\t" << r.ad_country << "\t\t" << r.ad_days << "\t\t" << r.ad_prices << endl;
    }
}

void Tourist::ad_modify()
{
    ifstream fp(adminf);
    if (!fp)
    {
        cerr << "Cannot open file " << adminf << endl;
        return;
    }

    string ad_code;
    cout << "\nENTER THE DESTINATION CODE TO BE MODIFIED: ";
    cin >> ad_code;

    vector<Tour> trips;
    string line;
    while (getline(fp, line))
    {
        trips.push_back(ad_unpack(line));
    }

    auto it = find_if(trips.begin(), trips.end(), [&](const Tour &t)
                      { return t.ad_code == ad_code; });

    if (it != trips.end())
    {
        cout << "Updating trip: " << it->ad_code << " " << it->ad_place << endl;
        cout << "Enter 1 to change the place, 2 to change the days, 3 to change the price, 0 to cancel: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter new destination place: ";
            cin >> it->ad_place;
        }
        else if (choice == 2)
        {
            cout << "Enter new number of days: ";
            cin >> it->ad_days;
        }
        else if (choice == 3)
        {
            cout << "Enter new price: ";
            cin >> it->ad_prices;
        }

        // Rewrite the updated data back to the file
        ofstream out(adminf, ios::trunc);
        for (const auto &t : trips)
        {
            ad_pack(t);
        }
    }
    else
    {
        cout << "Trip not found.\n";
    }
}

void Tourist::us_pack(const Tour &r)
{
    ofstream fp(userf, ios::app);
    if (!fp)
    {
        cerr << "Cannot open file " << userf << endl;
        return;
    }
    fp << r.us_name << "|" << r.us_phone << "|" << r.us_people << "|"
       << r.us_dcode << "|" << r.us_date << "|" << r.us_status << endl;
}

Tour Tourist::us_unpack(const string &line)
{
    Tour r;
    stringstream ss(line);
    getline(ss, r.us_name, '|');
    getline(ss, r.us_phone, '|');
    getline(ss, r.us_people, '|');
    getline(ss, r.us_dcode, '|');
    getline(ss, r.us_date, '|');
    getline(ss, r.us_status, '|');
    return r;
}

void Tourist::us_writedata()
{
    Tour r;
    cout << "Enter your name: ";
    cin >> r.us_name;
    cout << "Enter your contact number: ";
    cin >> r.us_phone;
    cout << "Enter the number of people: ";
    cin >> r.us_people;
    cout << "Enter the destination code (D-): ";
    cin >> r.us_dcode;
    cout << "Enter your date of journey (DD/MM/YY): ";
    cin >> r.us_date;
    cout << "Enter status (Confirm/Cancel): ";
    cin >> r.us_status;
    us_pack(r);
}

void Tourist::us_display()
{
    ifstream fp(userf);
    if (!fp)
    {
        cerr << "Cannot open file " << userf << endl;
        return;
    }

    string line;
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Sr No.\tNAME\t\tCONTACT NO\tTOTAL PEOPLE\tDATE\tDEST. CODE\tSTATUS\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    int c = 1;
    while (getline(fp, line))
    {
        Tour r = us_unpack(line);
        cout << c++ << "\t" << r.us_name << "\t\t" << r.us_phone << "\t\t" << r.us_people << "\t\t" << r.us_date << "\t\t" << r.us_dcode << "\t\t" << r.us_status << endl;
    }
}

void Tourist::us_search()
{
    ifstream fp(userf);
    if (!fp)
    {
        cerr << "Cannot open file " << userf << endl;
        return;
    }

    string us_name;
    cout << "Enter the name to search for: ";
    cin >> us_name;

    string line;
    while (getline(fp, line))
    {
        Tour r = us_unpack(line);
        if (r.us_name == us_name)
        {
            cout << "Reservation found for " << r.us_name << ":\n";
            cout << "Phone: " << r.us_phone << "\n";
            cout << "People: " << r.us_people << "\n";
            cout << "Date: " << r.us_date << "\n";
            cout << "Status: " << r.us_status << endl;
            return;
        }
    }

    cout << "Reservation not found.\n";
}

void Tourist::us_modify()
{
    ifstream fp(userf);
    if (!fp)
    {
        cerr << "Cannot open file " << userf << endl;
        return;
    }

    string us_name;
    cout << "Enter your name to modify the reservation: ";
    cin >> us_name;

    vector<Tour> reservations;
    string line;
    while (getline(fp, line))
    {
        reservations.push_back(us_unpack(line));
    }

    auto it = find_if(reservations.begin(), reservations.end(), [&](const Tour &t)
                      { return t.us_name == us_name; });

    if (it != reservations.end())
    {
        cout << "Updating reservation for " << it->us_name << endl;
        cout << "Enter new status (Confirm/Cancel): ";
        cin >> it->us_status;

        // Rewrite the updated data back to the file
        ofstream out(userf, ios::trunc);
        for (const auto &r : reservations)
        {
            us_pack(r);
        }
    }
    else
    {
        cout << "Reservation not found.\n";
    }
}

int main()
{
    Tourist obj;
    cout << "Welcome to the Tourist Reservation System\n";
    cout << "1. Admin\n";
    cout << "2. User\n";
    cout << "Enter any other key to exit\n";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "Admin Menu:\n";
        cout << "1. Add Trip\n";
        cout << "2. Modify Trip\n";
        cout << "3. View Trips\n";
        cout << "Enter your choice: ";
        int adminChoice;
        cin >> adminChoice;
        if (adminChoice == 1)
            obj.ad_writedata();
        else if (adminChoice == 2)
            obj.ad_modify();
        else if (adminChoice == 3)
            obj.ad_display();
        break;
    }
    case 2:
    {
        cout << "User Menu:\n";
        cout << "1. Make Reservation\n";
        cout << "2. Modify Reservation\n";
        cout << "3. View Reservations\n";
        cout << "4. Search Reservation\n";
        cout << "Enter your choice: ";
        int userChoice;
        cin >> userChoice;
        if (userChoice == 1)
            obj.us_writedata();
        else if (userChoice == 2)
            obj.us_modify();
        else if (userChoice == 3)
            obj.us_display();
        else if (userChoice == 4)
            obj.us_search();
        break;
    }
    default:
        return 0;
    }

    return 0;
}
