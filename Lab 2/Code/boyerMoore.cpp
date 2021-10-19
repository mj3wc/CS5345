//
// Created by wyatt on 5/5/2020.
//

#include "boyerMoore.h"

boyerMoore::boyerMoore() {
    cout << "Testing data set on Boyer-Moore algorithm" << endl;
    matches = 0;
    txt = "";
    pattern = "";
}
boyerMoore::boyerMoore(string t, string p) {
    cout << "\nBoyer Moore algorithm" << endl;
    matches = 0;
    txt = t;
    pattern = p;
    findMatches();
    cout << matches << " matches found" << endl;
}

// BoyerMoore with bad character heuristic
void boyerMoore::findMatches() {

    int i = pattern.length() - 1; //iterator for text, start at index = to the end of patterm
    int j = pattern.length() - 1; //iterator for the pattern start at the end
    bool match = false;

    while(i < (txt.length()- 1)){ // while not at end of txt
        if(txt[i] == pattern[j]){ //if charater matches one in text (loop will always begin at last character in pattern)
            if(j == 0){ // if at beginning of pattern match is found
               // cout << "Match found at " << i << endl;
               matches ++;
                match = true;
                i+= pattern.length()-1;
            }
            else{ // decrement iterators and start again
                i--;
                j--;
            }
        }

        else{  // no match increment iterators
            i = i + pattern.length() - min(j, (1 + last(txt[i]))); // i incremented to full pattern length or pos of char matching element in pattern
            j = pattern.length() -1; // set back to pattern length
        }
    }

    if(!match){ //if no matches found
        cout << "No matches found" << endl;
    }

}

int boyerMoore::last(char x) { // finds position of last instance of char in pattern
    for(int i = pattern.length()-1; i > 0; i--){ // (starts at pattern length - 2 because no need to check last element, will not cause a shift
        if(pattern[i] == x){ // if found in the pattern
            return i; // return position
        }
    }
    return -1;
}
