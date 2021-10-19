//
// Created by wyatt on 4/30/2020.
//

#ifndef STRING_MATCHING_TRIVIALMATCHING_H
#define STRING_MATCHING_TRIVIALMATCHING_H

#include <iostream>
#include <string>
using namespace std;

class trivialMatching {
private:
    string txt;
    string pattern;
    int matches;
public:
    trivialMatching();
    trivialMatching(string,string);
    void findMatches();
    bool checkRest(int&);

};


#endif //STRING_MATCHING_TRIVIALMATCHING_H
