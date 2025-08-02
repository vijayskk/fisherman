#include "main.hpp"

void help();
void thread_handler(int start,int stop);


int main(int argc, char *argv[])
{
    if (argc == 1 or (strcmp(argv[1], "-") == 0))
    {
        help();
        return 1;
    }

    int c, start, end;
    while ((c = getopt(argc, argv, "supah")) != -1)
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
        thread_handler(start,end); // TODO: Implement this
    }

    return 0;
}


void help(){
    cout << "\t'-s' - Scan system ports\n"
         << "\t'-u' - Scan user ports\n"
         << "\t'-p' - Scan private ports\n"
         << "\t'-a' - Scan all ports\n"
         << "\t'-h' - Print this menu.\n";
}

void count_open_ports(int start, int end){
    
}

void thread_handler(int start,int end){
    int max_threads = thread::hardware_concurrency();
    thread threadlist[max_threads];
    int interval = (end - start + 1)/max_threads;
    int thread_num;

    for (thread_num = 0; thread_num < max_threads; thread_num++)
    {
        int rightbound = start+interval;
        threadlist[thread_num] = thread(count_open_ports,start,rightbound);
        start = rightbound + 1;
    }

    for(thread_num = 0 ; thread_num < max_threads ; thread_num ++){
        threadlist[thread_num].join();
    }
    

}