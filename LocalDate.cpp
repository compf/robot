#include "LocalDate.hpp"
#include<iostream>
int8_t month_lengths[]= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
LocalDate::LocalDate(int8_t day, int8_t month, int16_t year)
{
    intern.tm_year = year;
    intern.tm_mon = month - 1;
    intern.tm_mday = day;
    intern.tm_hour = 11;
    intern.tm_sec=0;
    intern.tm_min=0;

    mktime(&intern);
    std::cout<<intern.tm_year+1900<<std::endl;
}
LocalDate LocalDate::random(int16_t min_year, int16_t max_year){
    int8_t month=rand()%12;
    int month_length=month_lengths[month];
    int8_t day=rand()%month_length+1;
    month++;
    int16_t year=min_year+rand()%(max_year-min_year)-1900;
    std::cout<<year<<std::endl;
    return LocalDate(day,month,year);
}
Weekday LocalDate::weekday()const
{
    return (Weekday)((intern.tm_wday + 6) % 7);
}
int8_t LocalDate::day()const
{
    return intern.tm_mday;
}
int8_t LocalDate::month()const
{
    return intern.tm_mon+1;
}
int16_t LocalDate::year()const{
    return intern.tm_year+1900;
}
void LocalDate::addDays(int8_t days){
    intern.tm_mday+=days;
    mktime(&intern);
}
  bool LocalDate::operator==(const LocalDate& date)const{
        return day()==date.day() && month()==date.month() && year()==date.year();
    }

