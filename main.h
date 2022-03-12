#pragma once

#include <iostream>
#include <iomanip>
#include <numeric>
#include <string>
#include <regex>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::accumulate;
using std::setprecision;
using std::vector;

using namespace std::chrono;
using hrClock = std::chrono::high_resolution_clock;

struct data {
    string name, surname;
    int exam;
    vector<int> grades;
};