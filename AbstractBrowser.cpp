#include "AbstractBrowser.hpp"
#include<filesystem>
AbstractBrowser::AbstractBrowser()
{

}

 void AbstractBrowser::storeFileCount(const std::string& path)
{
    file_count = getFileCount(path);
}
bool AbstractBrowser::checkDownloadStarted( const std::string& path)
{
    return getFileCount(path)!=file_count;
}
int AbstractBrowser::getFileCount( const std::string& path){
    int count=0;
    for(auto  entry: std::filesystem::directory_iterator(path) ){
        count++;
    }
    return count;
}
bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
