//
// Created by wyatt on 5/5/2020.
//

#ifndef STRING_MATCHING_BOYERMOORE_H
#define STRING_MATCHING_BOYERMOORE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class boyerMoore {
    private:
       string txt;
       string pattern;
        int matches;
    public:
    boyerMoore();
    boyerMoore(string, string);
    void findMatches();
    int last(char);
    void preprocess(string);

};


#endif //STRING_MATCHING_BOYERMOORE_H
