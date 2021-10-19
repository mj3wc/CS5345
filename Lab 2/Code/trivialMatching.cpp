//
// Created by wyatt on 4/30/2020.
//

#include "trivialMatching.h"
trivialMatching::trivialMatching() {
    cout << "Testing data set on trivial algorithm" << endl;
    matches = 0;
    txt = "";
    pattern = "";
}

trivialMatching::trivialMatching(string t, string p) {
    cout << "Trivial algorithm" << endl;
    matches =0;
    txt = t;
    pattern = p;
    findMatches();
    cout << matches << " matches found" << endl;
}

void trivialMatching::findMatches(){
    int position = 0;
    bool match = false;
    while(position < txt.length()) {
        if (txt[position] == pattern[0]) { //if first letter matches
            match = checkRest(position);
            if(match){
               // cout << "Match found start : " << position - pattern.length() + 1<< endl;
               matches++;
            }
        } else {
            position++; //else look at next charachter
        }
    }
}

bool trivialMatching::checkRest(int& position){  //checks if rest of string matches, updates position
    for(int i = 1; i < pattern.length(); i++){
        position++; //increment position
        if(txt[position] != pattern[i]){
            return false; // if doesnt match exit loop and return false
        }
    }
    return true; // if all match return true
}