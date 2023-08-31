#include<string>
#include "Robot.hpp"
class AbstractBrowser{
    public:
    AbstractBrowser();
    virtual void closeTab(Robot& rob)=0;
    virtual void storeFileCount(const std::string& path);
    virtual int getFileCount( const std::string& path);
    virtual bool checkDownloadStarted( const std::string& path);
    virtual bool checkDownloadEnded(const std::string& path)=0;
    private:
    int file_count;
};
bool hasEnding (std::string const &fullString, std::string const &ending) ;