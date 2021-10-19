//
// Created by wyatt on 5/6/2020.
//

#include "KMP.h"
KMP::KMP(){
    cout << "Testing data on Knuth-Morris-Pratt algorithm" << endl;
    matches = 0;
    txt = "";
    pattern = "";
}

KMP::KMP(string t, string p) {
    cout << "\nKMP algorithm" << endl;
    txt = t;
    pattern = p;
    matches = 0;
    preProcess();
    findMatches();
    cout << matches << " matches found" << endl;
}

void KMP::preProcess(){
    prefix.push_back(0);
    int i = 0; //match counter

    for(int j = 1; j < pattern.length(); j++){ //iterate through pattern length
        while(i > 0 && (pattern[i] != pattern[j])){
            i = prefix[i]; // set i back to zero
        }
        if(pattern[i] == pattern[j]){ //if they equal
            i++; //add one to mactch count
        }
        prefix.push_back(i); //push back i
    }
}
void KMP::findMatches(){
    int i = 0; //iterator of the text
    int j = 0; //iterator of the pattern
    int k = 0; //index of start of matches

    while((txt.length() - k) > pattern.length()){ // while not at end of pattern
        while(j < pattern.length() && (txt[i] == pattern[j])){ // if not at the end of the pattern and chars match
            i++; //look at next character
            j++;
        }
        if(j > pattern.length()-1){ // if reaches this statement a match was found
            //cout << "Match starting at " << k << endl;
            matches ++;
        }
        else if(prefix[j] > 0){  // if no more matches in suffix
            k = i - prefix[j]; // reset k
        }
        else{
            if(i == k){ // if the iterators =
                i++; // add one to i
            }
            else
                k = i; //if they dont equal catch k up to i
        }

        if(j > 1){
            j = prefix[j -1];
        }
    }

}