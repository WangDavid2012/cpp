#pragma once
#include <iostream>
using namespace std;

#define __DEBUG
#ifdef __DEBUG
#define mydebug std::cout
#else
#define mydebug 0 && std::cout
#endif