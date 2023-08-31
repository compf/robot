
#include "Robot.hpp"

#include <iostream>
#include <fstream>
#include <unordered_set>
#include "LocalDate.hpp"
#include "FirefoxBrowser.hpp"
#if linux
typedef uint8_t byte;
#endif

char BROWSER;
FirefoxBrowser firefox;
AbstractBrowser &getBrowser()
{
    if (BROWSER == 'f')
        return firefox;
    else
        throw 0;
}
std::unordered_set<LocalDate> unique_dates;

template <typename T>
T read_binary(std::ifstream &ifs)
{
    T dest;
    ifs.read(reinterpret_cast<char *>(&dest), sizeof(dest));
    return dest;
}
template <typename T>
void write_binary(std::ofstream &ofs, T val)
{
    ofs.write((char *)&val, sizeof(val));
}
void load_dates()
{
    std::ifstream fs("downloaded.bin", std::fstream::binary);

    while (fs.good())
    {
        byte day, month;
        uint16_t year;

        day = read_binary<int8_t>(fs);
        if (!fs.good())
            break;
        month = read_binary<int8_t>(fs);
        year = read_binary<int16_t>(fs);

        unique_dates.emplace(LocalDate(day, month, year));
        //std::cout << int(day) << '\t' << int(month) << '\t' << short(year + 1900) << std::endl;
    }
    fs.close();
}
int CALENDAR_POS[] = {0, 0};
int YEAR_POS[] = {0, 0};
int MONTH_POS[] = {0, 0};
int YEARMONTH_POS[] = {0, 0};
int CALENDAR_DATA[] = {0, 0, 0};
int SAVE_POS[] = {0, 0};
int lastMonth = 1;
int lastYear = 1948;
LocalDate lastDate(0,0,0);
std::string PATH;
void load_conf()
{
    std::ifstream ifs("conf.txt");
    std::string trash;
    ifs >> trash;
    ifs >> CALENDAR_POS[0];
    ifs >> CALENDAR_POS[1];

    ifs >> trash;
    ifs >> YEARMONTH_POS[0];
    ifs >> YEARMONTH_POS[1];

    ifs >> trash;
    ifs >> YEAR_POS[0];
    ifs >> YEAR_POS[1];

    ifs >> trash;
    ifs >> MONTH_POS[0];
    ifs >> MONTH_POS[1];

    ifs >> trash;
    ifs >> CALENDAR_DATA[0];
    ifs >> CALENDAR_DATA[1];
    ifs >> CALENDAR_DATA[2];

    ifs >> trash;
    ifs >> SAVE_POS[0];
    ifs >> SAVE_POS[1];

    ifs >> trash;
    ifs >> BROWSER;

    ifs >> trash;
    ifs >> PATH;
}

void moveToCalendar(Robot &rob)
{
    rob.mouseMove(CALENDAR_POS[0], CALENDAR_POS[1], 1000);
}
void moveToYearMonthSelection(Robot &rob)
{
    rob.mouseMove(YEARMONTH_POS[0], YEARMONTH_POS[1], 1000);
}
void moveToMonthSelection(Robot &rob)
{
    rob.mouseMove(MONTH_POS[0], MONTH_POS[1], 1000);
}

void moveToYearSelection(Robot &rob)
{
    rob.mouseMove(YEAR_POS[0], YEAR_POS[1], 1000);
}
void moveToSave(Robot &rob)
{
    rob.mouseMove(SAVE_POS[0], SAVE_POS[1],0);
}

void inputYear(Robot &rob, int16_t year)
{

    int diff = year - lastYear;
    int key;
    if (diff < 0)
    {
        key = rob.KEY_UP;
    }
    else if (diff > 0)
    {
        key = rob.KEY_DOWN;
    }
    else
    {
        return;
    }
    int diffAbs = abs(diff);
    for (int i = 0; i < diffAbs; i++)
    {
        rob.keyPress(key);
        rob.sleep_ms(1000);
    }
    lastYear = year;
}
void inputMonth(Robot &rob, int8_t month)
{

    int diff = month - lastMonth;
    int key;
    if (diff < 0)
    {
        key = rob.KEY_UP;
    }
    else if (diff > 0)
    {
        key = rob.KEY_DOWN;
    }
    else
    {
        return;
    }
    int diffAbs = abs(diff);
    for (int i = 0; i < diffAbs; i++)
    {
        rob.keyPress(key);
        rob.sleep_ms(1000);
    }
    lastMonth = month;
}
bool findDay(Robot &rob, LocalDate date)
{
    LocalDate firstDay(1, date.month(), date.year() - 1900);
    int x_pos = CALENDAR_DATA[0] + CALENDAR_DATA[2] * date.weekday();
    int y_pos = CALENDAR_DATA[1];
    int wkday_diff = date.weekday() - firstDay.weekday();
    LocalDate sameWkday(1 + wkday_diff, date.month(), date.year() - 1900);
    std::cout << "x pos:" << x_pos << std::endl;
    std::cout << "y pos:" << y_pos << std::endl;
    std::cout << "wkday diff:" << wkday_diff << std::endl;
    while (!(sameWkday == date))
    {
        sameWkday.addDays(7);
        y_pos += CALENDAR_DATA[2];
    }
    std::cout << "x pos:" << x_pos << std::endl;
    std::cout << "y pos:" << y_pos << std::endl;
    std::cout << "wkday diff:" << wkday_diff << std::endl;
    rob.mouseMove(x_pos, y_pos, 100);
    uint8_t r, g, b;
    rob.pixelColorCursor(r, g, b);
    if (r == 226 && g == 226 && b == 226)
    {
        std::cout << "invalid" << std::endl;
        return false;
    }
    return true;
}
void test_day()
{
    Robot rob;

    uint8_t r, g, b;
    while (true)
    {
        rob.pixelColorCursor(r, g, b);
        std::cout << int(r) << '\t' << int(g) << '\t' << int(b) << "hs" << std::endl;
        rob.sleep_ms(1000);
    }
}
bool step2(Robot &rob,LocalDate& dt)
{
    moveToYearSelection(rob);
    rob.sleep_ms(1000);
    rob.mouseClick(1, 0);
    rob.sleep_ms(1000);e
    LocalDate choosen(0, 0, 0);

    do
    {
        choosen = LocalDate::random(1950, 2018);

    } while (unique_dates.find(choosen) != unique_dates.end());
    std::cout << int(choosen.day()) << "." << int(choosen.month()) << "." << choosen.year() << std::endl;
    std::cout << choosen.year() << std::endl;
    inputYear(rob, choosen.year());
    rob.sleep_ms(1000);
    rob.keyPress(rob.KEY_ENTER);
    moveToMonthSelection(rob);
    rob.mouseClick(1, 100);
    inputMonth(rob, choosen.month());
    rob.keyPress(rob.KEY_ENTER);
    
    return findDay(rob, choosen);
}
void step3(Robot& rob)
{
    AbstractBrowser& browser = getBrowser();
    int counter=0;
    while(!browser.checkDownloadStarted(PATH)){
        rob.sleep_ms(1000);
    }
    while(!browser.checkDownloadEnded(PATH)){
        rob .sleep_ms(1000);
    }
    
}
void step4(){
    std::ofstream ofs("downloaded.bin",std::ios_base::app);
    write_binary<int8_t>(ofs,lastDate.day());
     write_binary<int8_t>(ofs,lastDate.month());
     write_binary<int16_t>(ofs,lastDate.year());
     ofs.close();


}
void step1()
{
    srand(time(0));
    //load_dates();
    load_conf();
    Robot rob;
    moveToCalendar(rob);
    rob.sleep_ms(1000);
    rob.mouseClick(1, 0);
    rob.sleep_ms(1000);
    moveToYearMonthSelection(rob);
    rob.sleep_ms(1000);
    rob.mouseClick(1, 0);
    rob.sleep_ms(1000);
    bool finished;
    do
    {
        finished = step2(rob,lastDate);
        std::cout << finished << std::endl;
    } while (!finished);
    getBrowser().storeFileCount(PATH);
    rob.mouseClick(1, 100);
    step3(rob);
    getBrowser().closeTab(rob);
    
}

int main()
{
    load_conf();
    //test_day();
    while(true)
    step1();
}
