#pragma once
#include <ctime>
#include <cstdint>
#include <functional>
enum Weekday
{
    Monday = 0,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

struct LocalDate
{
    LocalDate(int8_t day, int8_t month, int16_t year);
    bool operator==(const LocalDate &date) const;
    Weekday weekday() const;
    int8_t day() const;
    int8_t month() const;
    int16_t year() const;
    void addDays(int8_t days);
    static LocalDate random(int16_t min_year, int16_t max_year);

private:
    tm intern;
};
namespace std
{
    template <>
    struct hash<LocalDate>
    {
        std::size_t operator()(const LocalDate &date) const
        {
            return date.day() * 365 + date.month() * 31 + date.year();
        }
    };
} // namespace std
