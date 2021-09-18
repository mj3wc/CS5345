//Bubble, Insertion, Merge, & Selection sort from geeksforgeeks.com
//Quick Sort from stackOverflow - user: BuzzBox


#ifndef SORTER_H
#define SORTER_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Sorter {
protected:
    std::vector<T> data;

public:
    Sorter() {}
    Sorter(T& x):data(x) {}
    void setData(const std::vector<T>& x) {
        data = x;
    }
    virtual void sort() = 0;

};


template <typename T>
class MysterySorterA : public Sorter<T> {
public:

    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }
    virtual void sort() {
        // A function to implement bubble sort
            int i, j;
            bool swapped;
            for (i = 0; i < this->data.size()-1; i++){
                swapped = false;
            // Last i elements are already in place
            for (j = 0; j < this->data.size()-i-1; j++){
                if (this->data[j] > this->data[j+1]){
                    swap(&this->data[j], &this->data[j+1]);
                    swapped = true;
                }
             }

            if(swapped == false)
                break;

        }
        //std::cout << "Mystery Sorter A :: Bubble Sort" << std::endl;
    }


};

template <typename T>
class MysterySorterB : public Sorter<T> {
public:
    virtual void sort() {

        int i, key, j;
            for (i = 1; i < this->data.size(); i++)
            {
                key = this->data[i];
                j = i - 1;

                /* Move elements of arr[0..i-1], that are
                greater than key, to one position ahead
                of their current position */
                while (j >= 0 && this->data[j] > key)
                {
                   this->data[j + 1] = this->data[j];
                    j = j - 1;
                }
                this->data[j + 1] = key;
            }
        //std::cout << "Mystery Sorter B :: Insertion sort" << std::endl;
    }
};

template <typename T>
class MysterySorterC : public Sorter<T> {
public:
    void merge(vector<int>& data, int l, int m, int r)
    {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;

        /* create temp arrays */
        vector<int>L(n1);
        vector<int>R(n2);

        /* Copy data to temp arrays L[] and R[] */
        for (i = 0; i < n1; i++)
            L[i] = data[l + i];
        for (j = 0; j < n2; j++)
            R[j] = data[m + 1+ j];



        /* Merge the temp arrays back into arr[l..r]*/
        i = 0; // Initial index of first subarray
        j = 0; // Initial index of second subarray
        k = l; // Initial index of merged subarray
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                data[k] = L[i];
                i++;
            }
            else
            {
                data[k] = R[j];
                j++;
            }
            k++;
        }

        /* Copy the remaining elements of L[], if there
        are any */
        while (i < n1)
        {
            data[k] = L[i];
            i++;
            k++;
        }

        /* Copy the remaining elements of R[], if there
        are any */
        while (j < n2)
        {
            data[k] = R[j];
            j++;
            k++;
        }
    }

    /* l is for left index and r is right index of the
    sub-array of arr to be sorted */
    void mergeSort(vector<int>& data, int l, int r)
    {
        if (l < r)
        {
            // Same as (l+r)/2, but avoids overflow for
            // large l and h
            int m = l+(r-l)/2;

            // Sort first and second halves
            mergeSort(data, l, m);
            mergeSort(data, m+1, r);

            merge(data, l, m, r);
        }
    }
    virtual void sort() {
        mergeSort(this->data, 0, this->data.size() - 1);
        //std::cout << "Mystery Sorter C :: Merge sort" << std::endl;
    }
};

template <typename T>
class MysterySorterD : public Sorter<T> {
public:
    int partition(vector<int>& a,int start,int end)

    {

    int pivot=a[start],p1=start+1,i,temp;

    for(i=start+1;i<=end;i++)
    {

    if(a[i]<pivot)
        {
            if(i!=p1)
          {
                temp=a[p1];
                a[p1]=a[i];
                a[i]=temp;
          }    p1++;
        }
    }

            a[start]=a[p1-1];
            a[p1-1]=pivot;

    return p1-1;
    }




      void quicksort(vector<int>& a,int start,int end)
    {
     int p1;
     if(start<end)
    {
        p1=partition(a,start,end);
        quicksort(a,start,p1-1);
        quicksort(a,p1+1,end);
    }
    }
    virtual void sort() {
          quicksort(this->data,0,this->data.size()-1);
        //std::cout << "Mystery Sorter D :: Quick Sort" << std::endl;
    }
};

template <typename T>
class MysterySorterE : public Sorter<T> {
public:
    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    void selectionSort(vector<int>& arr, int n)
    {
        int i, j, min_idx;

        // One by one move boundary of unsorted subarray
        for (i = 0; i < n-1; i++)
        {
            // Find the minimum element in unsorted array
            min_idx = i;
            for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

            // Swap the found minimum element with the first element
            swap(&arr[min_idx], &arr[i]);
        }
    }

    virtual void sort() {
        selectionSort(this->data, this->data.size()-1);
        //std::cout << "Mystery Sorter E :: Selection Sort" << std::endl;
    }
};


#endif // SORTER_H
