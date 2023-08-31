#include "Robot.cpp"
#include "time.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <thread>
#include<cstdint>
struct MyKey
{
    unsigned int keycode;
    unsigned int weight;
    char char_code;
    MyKey(unsigned int k, char ch, unsigned int w)
    {
        keycode = k;
        weight = w;
        char_code = ch;
    }
    MyKey() {}
};
std::unordered_map<char, MyKey> keys;
std::vector<unsigned int> keyWheel;
Robot rob;
constexpr int PORT = 1997;
void setkey(char ch, unsigned int weight)
{
    keys[ch] = MyKey{rob.translateChar(ch), ch, weight};
}
void worker()
{
    std::cout<<"start"<<std::endl;
    sockaddr_in servaddr, cliaddr;
    int sockfd;
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len, n;
    unsigned char buffer[4];
    len = sizeof(cliaddr); //len is value/resuslt
    std::cout<<"init finsihed"<<std::endl;
    while (true)
    {
       
        n = recvfrom(sockfd, buffer, 4,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        std::cout<<"len "<<n<<std::endl;

        std::uint8_t ch=buffer[0];
        
        std::uint16_t weight=buffer[2]|buffer[3]<<8;;
        std::cout<<"received  "<<ch<<" "<<int(buffer[2]) << " "<<int(buffer[3])<<" "<<weight<<std::endl;
        keys[ch].weight=weight;
    }
}
void parseConf()
{
    std::ifstream inp("pokemon_control.txt");
    std::string dummy;
    char ch;
    unsigned int weight;
    while (inp.good())
    {

        inp >> dummy;
        inp >> ch;

        inp >> weight;

        unsigned long code = rob.translateChar(ch);

        keys[ch]=MyKey{code,ch,weight};
        for (int i = 0; i < weight; i++)
        {
            keyWheel.push_back(code);
        }
    }
    std::cout << keyWheel.size() << std::endl;
}

int main()
{

    srand(time(NULL));
    parseConf();
    std::thread worker_thread{worker};
   
  
    //return 0;
    while (true)
    {
        int sum=0;
        for(auto p:keys){
            sum+=p.second.weight;
        }
        int key = rand() % sum;
        for(auto p:keys){
            key-=p.second.weight;
            if(key<p.second.weight){
                rob.keyPress(p.second.keycode);
                rob.sleep(1000);
            }
        }
        //ee rob.keyPress(keyWheel[key]);
        
    }
}