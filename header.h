#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <climits>
#include <fstream>
#include <streambuf>
#include <chrono>
#include <algorithm>
#include<iterator>
#include <cassert>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using std::to_string;

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

string hashFunction(string);

class Timer {
private:
	using hrClock = std::chrono::high_resolution_clock;
	using durationDouble = std::chrono::duration<double>;
	std::chrono::time_point<hrClock> start;
public:
	Timer() : start{ hrClock::now() } {}
	void reset() {
		start = hrClock::now();
	}
	double elapsed() const {
		return durationDouble (hrClock::now() - start).count();
	}
};

#endif // HEADER_H_INCLUDED
