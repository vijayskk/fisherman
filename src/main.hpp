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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>

using std::thread;
using std::mutex;
using std::lock_guard;
using std::vector;
using std::cout;

static vector<int> open_ports;
static mutex vec_mtx;