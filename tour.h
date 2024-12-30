#ifndef TOUR_H
#define TOUR_H

#include <string>

struct Tour
{
    // Fields for admin
    std::string ad_place, ad_code, ad_country, ad_days, ad_prices;

    // Fields for user
    std::string us_phone, us_name, us_people, us_date, us_status, us_dcode;
};

#endif // TOUR_H