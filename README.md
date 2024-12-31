# Tourist Reservation System

This project is a Tourist Reservation System implemented in C++. It allows users to make, modify, search, and display reservations for trips. The admin can add trips and set prices for each trip.

## Features

### Admin
- Add a new trip with details such as destination code, place, country, number of days, and price per person.
- Set the price per person for each trip.

### User
- Make a reservation by providing details such as name, contact number, number of people, destination code, date of journey, and status.
- Modify an existing reservation.
- Search for a reservation by reservation ID (name).
- Display all reservations for a specific user based on their contact number.

## Files

- `admin.h` and `admin.cpp`: Contains the implementation of the Admin class and its methods.
- `user.h` and `user.cpp`: Contains the implementation of the User class and its methods.
- `Tour.h`: Contains the definition of the Tour struct used for storing trip and reservation details.

## How to Run

1. **Compile the project**:
   Use `g++` to compile the project files. For example:
   ```sh
   g++ -std=c++11 -o TouristSystem admin.cpp user.cpp
2. Run THe Executable
3. ./TouristSystem     

# Seasonal Packages
1. **Feature:** Offer special packages for certain times of the year (e.g., summer or winter).
2. **Benefit:** Creates an attractive offering for users during peak seasons.
