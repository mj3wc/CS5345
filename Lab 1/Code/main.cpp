#include <iostream>
#include <vector>
#include "sorterhelper.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

int main()
{
    auto start = high_resolution_clock::now();                //start time
    sorterHelper tester;                                      // sorterHelper object
    tester.test1();                                           //start test
    tester.output();                                          //output determiend methods
                                                              //call sort method
    auto end = high_resolution_clock::now();                  //send time
    auto duration = duration_cast<microseconds>(end - start); //to microseconds

    cout << "Execution Time : " << duration.count() << " " << endl;
    return 0;
}

sorterHelper::sorterHelper()
{
    //initalize MysterySorter objects
    exp[0] = new MysterySorterA<int>();
    exp[1] = new MysterySorterB<int>();
    exp[2] = new MysterySorterC<int>();
    exp[3] = new MysterySorterD<int>();
    exp[4] = new MysterySorterE<int>();

    for (int x = 0; x < 5; x++)
    {
        algorithms[x] = 0;
    }
}

sorterHelper::~sorterHelper()
{
    //destructor
}

//first test: sorts out Bubble sort and Insertion sort by using sorted data to find two fastest, as both are O(n) for best case(sorted data)
void sorterHelper::test1()
{
    vector<int> data;
    //data set 0-999 sorted
    for (int x = 0; x < 1000; x++)
    {
        data.push_back(x);
    }

    //set data in each sorting algorithm
    for (int x = 0; x < 5; x++)
    {
        exp[x]->setData(data);
    }

    int seconds[5];

    //Times each sort algorithm and stores in seconds array
    for (int x = 0; x < 5; x++)
    {
        auto start = high_resolution_clock::now();                //start time
        exp[x]->sort();                                           //call sort method
        auto end = high_resolution_clock::now();                  //send time
        auto duration = duration_cast<microseconds>(end - start); //to microseconds
        seconds[x] = duration.count();                            //to int, store into array
    }

    int fastestIndex = 0;
    int nextFastestIndex = 1;
    int currFastestTime = seconds[0];
    int nextFastestTime;

    //find the two fastest times,seperates bubble and insertion
    for (int x = 1; x < 5; x++)
    {
        if (seconds[x] < currFastestTime)
        {
            nextFastestTime = currFastestTime;
            currFastestTime = seconds[x];
            nextFastestIndex = fastestIndex;
            fastestIndex = x;
        }
        else if (seconds[x] < nextFastestTime)
        {
            nextFastestTime = seconds[x];
            nextFastestIndex = x;
        }
    }
    test2(fastestIndex, nextFastestIndex); //sends bubble and insertion to another test to determine which is which

    int remainder[3];
    int count = 0;
    //store the remaining sorts algorithms into an array
    for (int x = 0; x < 5; x++)
    {
        if (x != fastestIndex && x != nextFastestIndex)
        {
            remainder[count] = x;
            count++;
        }
    }
    test3(remainder); //test to seperate the remaining 3 algorithms
}

//test to determine which sorting algortim is bubble and which is insertion, Insertion is faster when sorting unsorted data
void sorterHelper::test2(int fast, int nextFast)
{
    vector<int> data;
    //initalize data with 100 random ints
    for (int x = 0; x < 100; x++)
    {
        int a = rand() % 100 + 1;
        data.push_back(a);
    }
    //set the sorting algoritms data
    exp[fast]->setData(data);
    exp[nextFast]->setData(data);

    int seconds[2];

    //time first sorting algortihm
    auto start = system_clock::now(); //start time
    exp[fast]->sort();                //sort the data
    auto end = system_clock::now();   //end time
    auto duration = duration_cast<microseconds>(end - start);
    seconds[0] = duration.count();

    //time second sorting algorithm
    start = system_clock::now(); //start time
    exp[nextFast]->sort();       //sort the data
    end = system_clock::now();   //end time
    duration = duration_cast<microseconds>(end - start);
    seconds[1] = duration.count();

    //which ever sorting algorithm is faster it is insertion
    if (seconds[0] < seconds[1])
    {
        setAlgorithms(fast, 2);
        setAlgorithms(nextFast, 1);
    }
    else
    {
        setAlgorithms(fast, 1);
        setAlgorithms(nextFast, 2);
    }
}

//test 3 detrmines which sorting algorithm is merge, as merge is the fastest with a large sorted data set
void sorterHelper::test3(int index[])
{
    vector<int> data;
    //set data with 0-1499 sorted
    for (int x = 0; x < 1500; x++)
    {
        data.push_back(x);
    }
    //set data for each sorting algorithm
    for (int x = 0; x < 3; x++)
        exp[index[x]]->setData(data);

    int seconds[3];

    //time the different sorting algortims
    for (int x = 0; x < 3; x++)
    {
        auto start = system_clock::now(); //start time
        exp[index[x]]->sort();
        auto end = system_clock::now(); //end time
        auto duration = duration_cast<microseconds>(end - start);
        seconds[x] = duration.count();
    }
    //which ever method is the fastest is merge sort
    if (seconds[0] < seconds[1] && seconds[0] < seconds[2])
    {
        setAlgorithms(index[0], 3);
        test4(index[1], index[2]);
    }

    else if (seconds[1] < seconds[0] && seconds[1] < seconds[2])
    {
        setAlgorithms(index[1], 3);
        test4(index[0], index[2]);
    }

    else
    {
        setAlgorithms(index[2], 3);
        test4(index[0], index[1]);
    }
}

//test to determine which sorting algorithm is quick and insertion, as quick sort is faster for a large unsorted data set
void sorterHelper::test4(int sort1, int sort2)
{
    vector<int> data;
    //set data with 1000 unsorted random ints from 1-100
    for (int x = 0; x < 1000; x++)
    {
        int a = rand() % 100 + 1;
        data.push_back(a);
    }
    //set the data for each sorting algorithm
    exp[sort1]->setData(data);
    exp[sort2]->setData(data);

    int seconds[2];

    //time first sorting algorithm
    auto start = system_clock::now(); //start time
    exp[sort1]->sort();               //sort the data
    auto end = system_clock::now();   //end time
    auto duration = duration_cast<microseconds>(end - start);
    seconds[0] = duration.count();

    //time second sorting algorithm
    start = system_clock::now(); //start time
    exp[sort2]->sort();          //sort the data
    end = system_clock::now();   //end time
    duration = duration_cast<microseconds>(end - start);
    seconds[1] = duration.count();

    //which ever sorting algorithm is faster is quick sort
    if (seconds[0] < seconds[1])
    {
        setAlgorithms(sort1, 4);
        setAlgorithms(sort2, 5);
    }
    else
    {
        setAlgorithms(sort1, 5);
        setAlgorithms(sort2, 4);
    }
}

//output the determined sorting algortims to MysterySorter they were found to be
void sorterHelper::output()
{
    char letter = 'A';
    for (int x = 0; x < 5; x++)
    {
        cout << "MysterySorter" << (char)(letter + x) << " is ";
        if (algorithms[x] == 1)
        {
            cout << "BubbleSort" << endl;
        }
        else if (algorithms[x] == 2)
        {
            cout << "InsertionSort" << endl;
        }

        else if (algorithms[x] == 3)
        {
            cout << "MergeSort" << endl;
        }

        else if (algorithms[x] == 4)
        {
            cout << "QuickSort" << endl;
        }
        else if (algorithms[x] == 5)
        {
            cout << "SelectionSort" << endl;
        }
    }

    cout << "\n"
         << endl;
}

//store the algortims in the position they were determined 0 = A, 1 = B, 2 = C, 3 = D, 4 = E
void sorterHelper::setAlgorithms(int index, int algorithm)
{
    algorithms[index] = algorithm;
}
