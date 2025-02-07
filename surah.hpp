#ifndef SURAH_HPP
#define SURAH_HPP
#include <string>
using namespace std;

struct Surah
{
    string surahName;
    string director;
    string type;
    Surah *next;
    Surah *prev;
    Surah(string name ):surahName(name),next(nullptr),prev(nullptr){}
};

#endif
