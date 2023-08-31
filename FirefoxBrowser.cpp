#include "FirefoxBrowser.hpp"
#include<filesystem>
void FirefoxBrowser::closeTab(Robot& rob)
{
    std::vector<unsigned int > v;
    v.push_back(rob.KEY_CTRL);
    v.push_back(rob.translateChar('W'));
    rob.keyPress(v);
}
bool FirefoxBrowser::checkDownloadEnded(const std::string& path)
{
    for (auto entry : std::filesystem::directory_iterator(path))
    {
       bool b= hasEnding( entry.path().string(),".part");
       if(b)return false;
    }
    return true;
}