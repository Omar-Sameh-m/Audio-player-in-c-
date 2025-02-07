#ifndef SHAIKH_HPP
#define SHAIKH_HPP
#include"surah.hpp"
#include <string>
using namespace std;

struct Shaikh
{
    string shaikh_name;
    Shaikh *next;
    Shaikh *prev;
    Surah *headSurah;
    Shaikh(string name):shaikh_name(name),next(nullptr),prev(nullptr),headSurah(nullptr){}
    
};

#endif
