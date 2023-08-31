#include "AbstractBrowser.hpp"
class FirefoxBrowser: public AbstractBrowser{
    public:
    void closeTab(Robot& rob)override;
    bool checkDownloadEnded(const std::string& path)override;

};