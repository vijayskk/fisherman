#include "main.hpp"
#include "common.hpp"

void help();
void thread_handler(int start,int stop,std::string ip);
void common_scan(std::string ip);

int main(int argc, char *argv[])
{
    if (argc == 1 or (strcmp(argv[1], "-") == 0))
    {
        help();
        return 1;
    }
    std::string ip = argc < 3?"127.0.0.1":argv[2];
    
    int c, start, end;
    bool usecommon = false;
    while ((c = getopt(argc, argv, "supcah")) != -1)
    {
        switch (c)
        {
        case 's':
            start = 0;
            end = 1023;
            break;
        case 'u':
            start = 1024;
            end = 49151;
            break;
        case 'p':
            start = 49152;
            end = 65535;
            break;
        case 'c':
            usecommon = true;
            break;
        case 'a':
            start = 0;
            end = 65535;
            break;
        case 'h':
            help();
            break;
        default:
            help();
            break;
        }
        if (!usecommon)
        {
            thread_handler(start,end,ip);
        }else{
            common_scan(ip);
        }


    }

    return 0;
}


void help(){
    cout << "=============================\n";
    cout << "     🐟 Fisherman v1.0       \n";
    cout << "  Fast TCP Port Scanner      \n";
    cout << "=============================\n\n";
    cout << "Usage:\n";
    cout << "  fisherman [OPTION] [TARGET_IP]\n\n";
    cout << "Options:\n";
    cout << "  -s    Scan system ports (0 - 1023)\n";
    cout << "  -u    Scan user ports   (1024 - 49151)\n";
    cout << "  -p    Scan private ports (49152 - 65535)\n";
    cout << "  -c    Scan commonly used ports\n";
    cout << "  -a    Scan all ports (0 - 65535)\n";
    cout << "  -h    Display this help message\n\n";
    cout << "Example:\n";
    cout << "  fisherman -c 192.168.1.10\n\n";
    exit(0);
}

bool is_open(std::string ip , int port,int timeout_ms = 20){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0)
    {
        return false;
    }
    fcntl(sockfd,F_SETFL,O_NONBLOCK); // Make the connect return immedeately. No waiting
    sockaddr_in address;
    memset(&address,0,sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET,ip.c_str(),&address.sin_addr);

    int res = connect(sockfd,(sockaddr *)&address,sizeof(address));
    if (res == 0)
    {
        // immediate connection
        //cout<<port<< " OPEN\n";
        close(sockfd);
        return true;
    }else if(errno != EINPROGRESS){
        // Immediate fail
        //cout<<port<< " CLOSED\n";
        close(sockfd);
        return false;
    }
    fd_set writefds; // file descriptor group for write checking.
    FD_ZERO(&writefds); // fd_set is not auto cleared. this will clear it. This is a macro
    FD_SET(sockfd,&writefds); // watch this socket and register it in writefds.

    timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    
    int sel = select(sockfd + 1,nullptr,&writefds,nullptr,&tv); // this will watch for writablity and for the given time. This is a system call.
    if (sel<=0)
    {
        // Timeout or error.
        close(sockfd);
        return false;
    }

    int sockerror;
    socklen_t len = sizeof(sockerror);
    getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&sockerror,&len); // this grabs why the socket is writable. wether it is success or a failiure. select() wont give that.
    
    close(sockfd);
    //(sockerror == 0)? cout<<port<< " OPEN\n" : cout<<port<< " CLOSED\n";
    return sockerror == 0;
}

void count_open_ports(int start, int end,std::string ip){
    for (int port = start; port <= end; port++)
    {
        if (is_open(ip,port))
        {
            lock_guard<mutex> guard(vec_mtx);
            open_ports.push_back(port);
        }
        //cout<<"SCANNED "<<port<<"\n";
    }
    
    
}

void print_ports(){
    cout << "\n========== Scan Results ==========\n";
    if (open_ports.empty()) {
        cout << "No open ports found.\n";
    } else {
        for(int port : open_ports){
            if ((common_services.count(port) > 0))
            {
                cout << "[+] Port " << port << " OPEN - " << common_services[port] << "\n";
            } else {
                cout << "[+] Port " << port << " OPEN - Unknown service\n";
            }
        }
    }
    cout << "==================================\n";
}

void thread_handler(int start,int end,std::string ip){
    int max_threads = 32;
    thread threadlist[max_threads];
    int interval = (end - start + 1)/max_threads;
    int thread_num;
    cout<< "Scanning...\n";
    for (thread_num = 0; thread_num < max_threads; thread_num++)
    {
        int rightbound = start+interval;
        threadlist[thread_num] = thread(count_open_ports,start,rightbound,ip);
        start = rightbound;
    }

    for(thread_num = 0 ; thread_num < max_threads ; thread_num ++){
        threadlist[thread_num].join();
    }
    
    std::sort(open_ports.begin(),open_ports.end());
    print_ports();
}

void common_scan(std::string ip){
    cout<< "Scanning...\n";
    for (auto port : common_ports)
    {
        if (is_open(ip,port))
        {
            lock_guard<mutex> guard(vec_mtx);
            open_ports.push_back(port);
        }
    }
    print_ports();
}