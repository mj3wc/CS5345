

#include <iostream>
#include <fstream>
#include <string>
#include "trivialMatching.h"
#include "boyerMoore.h"
#include "KMP.h"
#include "algorithm"
#include <chrono>

using namespace std::chrono;
using namespace std;
/*
//checks if file open, if not prompt for user to enter one and retry
bool checkOpen(string &fileName, ifstream &file)
{
    if (file.is_open())
    {
        return true;
    }
    else
    {
        cout << "Please enter a valid file name" << endl;
        cin >> fileName;
        file.open(fileName);
        return false;
    }
}
*/

int main()
{
    /*
    ifstream file;
    string filename = "text.txt";
    file.open(filename); // set file name (** Change to arg **)
    bool open = false;
    int count = 0;

    // checks if opens, prompts user to try again if fails
    while (!open && count < 10)
    {                                     // maximum of 10 failed attempts
        open = checkOpen(filename, file); //function to check if open
        count++;
    }

    if (count == 10)
    { // if maximum attempts reached, exit the program
        cout << "Maximum attempts reached. Exiting Program..." << endl;
        exit(-1);
    }
*/
    //read in the whole text file into one string
    string content;
    content = "COVID-19 is caused by a coronavirus called SARS-CoV-2. Older adults and people who have severe underlying medical conditions like heart or lung disease or diabetes seem to be at higher risk for developing more serious complications from COVID-19 illness. It is thought to spread mainly from person to person, mainly through respiratory droplets produced when an infected person coughs or sneezes. These droplets can land in the mouths or noses of people who are nearby or possibly be inhaled into the lungs. Spread is more likely when people are in close contact with one another (within about 6 feet). COVID-19 seems to be spreading easily and sustainably in the community community spread in many affected geographic areas.Community spread means people have been infected with the virus in an area, including some who are not sure how or where they became infected. Coronavirus disease (COVID-19) is an infectious disease caused by a newly discovered coronavirus.Most people infected wih the COVID-19 virus will experience ";

    //content.assign((istreambuf_iterator<char>(file)),
    //(istreambuf_iterator<char>()));
    content.erase(remove(content.begin(), content.end(), '\n'), content.end());
    content.erase(remove(content.begin(), content.end(), ' '), content.end());
    string find;
    cout << "Please enter a search" << endl;
    cin >> find;
    find.erase(remove(find.begin(), find.end(), ' '), find.end());
    cout << "Searching for : " << find << endl;
    auto start = high_resolution_clock::now(); //start time
    trivialMatching trivial(content, find);    //trivial algorithm
    auto end = high_resolution_clock::now();   //send time
    auto duration = duration_cast<nanoseconds>(end - start);
    int seconds = duration.count();
    cout << seconds << " microseconds" << endl;

    start = high_resolution_clock::now();
    boyerMoore BM(content, find);       //boyerMoore algorithm
    end = high_resolution_clock::now(); //send time
    duration = duration_cast<microseconds>(end - start);
    seconds = duration.count();
    cout << seconds << " microseconds" << endl;

    start = high_resolution_clock::now();
    KMP kmp(content, find);             //Knuth Morris Pratt algorithm
    end = high_resolution_clock::now(); //send time
    duration = duration_cast<microseconds>(end - start);
    seconds = duration.count();
    cout << seconds << " microseconds" << endl;

    cout << "Processes Finished" << endl;
    return 0;
}

trivialMatching::trivialMatching()
{
    cout << "Testing data set on trivial algorithm" << endl;
    matches = 0;
    txt = "";
    pattern = "";
}

trivialMatching::trivialMatching(string t, string p)
{
    cout << "Trivial algorithm" << endl;
    matches = 0;
    txt = t;
    pattern = p;
    findMatches();
    cout << matches << " matches found" << endl;
}

void trivialMatching::findMatches()
{
    int position = 0;
    bool match = false;
    while (position < txt.length())
    {
        if (txt[position] == pattern[0])
        { //if first letter matches
            match = checkRest(position);
            if (match)
            {
                // cout << "Match found start : " << position - pattern.length() + 1<< endl;
                matches++;
            }
        }
        else
        {
            position++; //else look at next charachter
        }
    }
}

bool trivialMatching::checkRest(int &position)
{ //checks if rest of string matches, updates position
    for (int i = 1; i < pattern.length(); i++)
    {
        position++; //increment position
        if (txt[position] != pattern[i])
        {
            return false; // if doesnt match exit loop and return false
        }
    }
    return true; // if all match return true
}

KMP::KMP()
{
    cout << "Testing data on Knuth-Morris-Pratt algorithm" << endl;
    matches = 0;
    txt = "";
    pattern = "";
}

KMP::KMP(string t, string p)
{
    cout << "\nKMP algorithm" << endl;
    txt = t;
    pattern = p;
    matches = 0;
    preProcess();
    findMatches();
    cout << matches << " matches found" << endl;
}

void KMP::preProcess()
{
    prefix.push_back(0);
    int i = 0; //match counter

    for (int j = 1; j < pattern.length(); j++)
    { //iterate through pattern length
        while (i > 0 && (pattern[i] != pattern[j]))
        {
            i = prefix[i]; // set i back to zero
        }
        if (pattern[i] == pattern[j])
        {        //if they equal
            i++; //add one to mactch count
        }
        prefix.push_back(i); //push back i
    }
}
void KMP::findMatches()
{
    int i = 0; //iterator of the text
    int j = 0; //iterator of the pattern
    int k = 0; //index of start of matches

    while ((txt.length() - k) > pattern.length())
    { // while not at end of pattern
        while (j < pattern.length() && (txt[i] == pattern[j]))
        {        // if not at the end of the pattern and chars match
            i++; //look at next character
            j++;
        }
        if (j > pattern.length() - 1)
        { // if reaches this statement a match was found
            //cout << "Match starting at " << k << endl;
            matches++;
        }
        else if (prefix[j] > 0)
        {                      // if no more matches in suffix
            k = i - prefix[j]; // reset k
        }
        else
        {
            if (i == k)
            {        // if the iterators =
                i++; // add one to i
            }
            else
                k = i; //if they dont equal catch k up to i
        }

        if (j > 1)
        {
            j = prefix[j - 1];
        }
    }
}

boyerMoore::boyerMoore()
{
    cout << "Testing data set on Boyer-Moore algorithm" << endl;
    matches = 0;
    txt = "";
    pattern = "";
}
boyerMoore::boyerMoore(string t, string p)
{
    cout << "\nBoyer Moore algorithm" << endl;
    matches = 0;
    txt = t;
    pattern = p;
    findMatches();
    cout << matches << " matches found" << endl;
}

// BoyerMoore with bad character heuristic
void boyerMoore::findMatches()
{

    int i = pattern.length() - 1; //iterator for text, start at index = to the end of patterm
    int j = pattern.length() - 1; //iterator for the pattern start at the end
    bool match = false;

    while (i < (txt.length() - 1))
    { // while not at end of txt
        if (txt[i] == pattern[j])
        { //if charater matches one in text (loop will always begin at last character in pattern)
            if (j == 0)
            { // if at beginning of pattern match is found
                // cout << "Match found at " << i << endl;
                matches++;
                match = true;
                i += pattern.length() - 1;
            }
            else
            { // decrement iterators and start again
                i--;
                j--;
            }
        }

        else
        {                                                          // no match increment iterators
            i = i + pattern.length() - min(j, (1 + last(txt[i]))); // i incremented to full pattern length or pos of char matching element in pattern
            j = pattern.length() - 1;                              // set back to pattern length
        }
    }

    if (!match)
    { //if no matches found
        cout << "No matches found" << endl;
    }
}

int boyerMoore::last(char x)
{ // finds position of last instance of char in pattern
    for (int i = pattern.length() - 1; i > 0; i--)
    { // (starts at pattern length - 2 because no need to check last element, will not cause a shift
        if (pattern[i] == x)
        {             // if found in the pattern
            return i; // return position
        }
    }
    return -1;
}
