#include "main.hpp"


void scan();


int main(int argc, char const *argv[])
{
    int num_of_threads = thread::hardware_concurrency();
    cout << "Available threads = " << num_of_threads << "\n";
    scan();
    for(auto i : open_ports){
        cout<< i << "\n";
    }
    return 0;
}

void scan(){
    for (int i = 0; i < 65535; i++)
    {
        int sockfd;
        struct sockaddr_in address;

        if (inet_pton(AF_INET,"127.0.0.1",&address.sin_addr) < 1) // Checks for ip can be binded or not
        {
            std::cerr << "Problem Loading the ip address!!\n";
            exit(EXIT_FAILURE);
        }
        
        memset(&address,0,sizeof(address));
        address.sin_family = AF_INET; // IPv4
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        address.sin_port = htons(i);

        if ((sockfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
        {
            close(sockfd);
            continue;
        }
        if (connect(sockfd,(struct sockaddr *)&address,sizeof(address)) == 0)
        {
            open_ports.push_back(i);
        }
        close(sockfd);
    }
    
}