#include <iostream>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <thread>
#include <algorithm>
#include <vector>
#include <mutex>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#pragma once
#include <atomic>
extern std::atomic<int> ports_scanned;

using std::cout;
using std::lock_guard;
using std::mutex;
using std::thread;
using std::vector;

static vector<int> open_ports;
static mutex vec_mtx;