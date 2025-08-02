#include <iostream>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <algorithm>
#include <vector>
#include <mutex>

using std::thread;
using std::mutex;
using std::lock_guard;
using std::vector;
using std::cout;

static vector<int> open_ports;
static mutex vec_mtx;