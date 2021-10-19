//
// Created by wyatt on 5/6/2020.
//

#ifndef STRING_MATCHING_KMP_H
#define STRING_MATCHING_KMP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class KMP {
private:
    vector<int> prefix;
    string txt;
    string pattern;
    int matches;

public:
    KMP();
    KMP(string, string);
    void preProcess();
    void findMatches();
};


#endif //STRING_MATCHING_KMP_H
