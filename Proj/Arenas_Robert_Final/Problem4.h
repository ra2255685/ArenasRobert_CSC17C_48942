/* 
 * File:   Problem4.h
 * Author: Robert Arenas Id: 2255685
 *
 * Created on December 18, 2015, 10:10 AM
 */

#ifndef PROBLEM4_H
#define PROBLEM4_H

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

class Sorts{
public:
    //constructor 
    Sorts();
    //prints array;
    void print(int [], const int&);
    
    //sort functions borrowed from SortComparisons class example of the 
    //class github page for testing
    void quickSort(int [], int, int);
    void merge_sort(int*, const int, const int);
    void heapsort(int [], int);
    
    //sort functions borrowed from chapter 8 of Gaddis book for testing
    void bubble(int [],const int);
    void selection(int [],const int);
    
    //insertion sort borrowed from 
    //http://www.algolist.net/Algorithms/Sorting/Insertion_sort
    //for testing
    void insertion(int [],const int);
    
    //function to create an array of top values returns pointer to 
    //array created
    int *topElements(int [], int);
    //show sorts to choose from
    void sortOptions();
    //answer question on final
    void findings();
    
private:
    
    //utility functions for the sorts
    int pivot(int [], int, int);
    void swap(int&, int&);
    void merge(int*,int,const int, const int);
    void buildheap(int [], int);
    void heapify(int [], int, int);
    
};

//constructor
Sorts::Sorts(){
    
}
/*
 * Print an array.
 * @param a - The array.
 * @param N - The size of the array.
*/
void Sorts::print(int a[], const int& N){
    for(int i = 0 ; i < N ; i++)
        cout << "array[" << i << "] = " << a[i] << endl;
}
/*
 * Quicksort.
 * @param a - The array to be sorted.
 * @param first - The start of the sequence to be sorted.
 * @param last - The end of the sequence to be sorted.
*/
void Sorts::quickSort(int a[], int first, int last){
    int pivotElement;
 
    if(first < last)
    {
        pivotElement = pivot(a, first, last);
        quickSort(a, first, pivotElement-1);
        quickSort(a, pivotElement+1, last);
    }
}
/*
 * Find and return the index of pivot element.
 * @param a - The array.
 * @param first - The start of the sequence.
 * @param last - The end of the sequence.
 * @return - the pivot element
*/
int Sorts::pivot(int a[], int first, int last){
    int  p = first;
    int pivotElement = a[first];
 
    for(int i = first+1 ; i <= last ; i++)
    {
        /* If you want to sort the list in the other order, change "<=" to ">" */
        if(a[i] <= pivotElement)
        {
            p++;
            swap(a[i], a[p]);
        }
    }
 
    swap(a[p], a[first]);
 
    return p;
}
/**
 * Swap the parameters.
 * @param a - The first parameter.
 * @param b - The second parameter.
*/
void Sorts::swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void Sorts::merge_sort(int* A, const int p, const int r){
    if (p < r) 
    {
        int q = (p+r)/2;
        merge_sort(A, p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
}
void Sorts::merge(int* A,int p,const int q, const int r){
    const int n_1=q-p+1;
    const int n_2=r-q;
    int* L = new int [n_1+1];
    int* R = new int [n_2+1];
    L[n_1]=0;
    R[n_2]=0;
    for(int i = 0; i < n_1; i++) 
        L[i] = A[p+i];
    for (int j = 0; j < n_2; j++)
        R[j] = A[q+j+1];

    int i=0;
    int j=0;
    // for(int k = p; k <= r; p++)   broken code
    int k;
    for(k=p; k <= r && i < n_1 && j < n_2; ++k)
    {
        if(L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;        
        }
    }
    // Added the following two loop.
    // Note only zero or one loop will actually activate.
    while (i < n_1) {A[k++] = L[i++];}
    while (j < n_2) {A[k++] = R[j++];}
}

void Sorts::heapsort(int A[], int length){
    int heapsize = length;
	
	buildheap(A, length);	//Take the unsorted list and make it a heap
	for (int i = length-1; i >=1; i--)
	{
		swap(A[0], A[i]);
		heapsize--;
		heapify(A, heapsize, 0);		
	}
}

void Sorts::buildheap(int A[], int length){
    for (int i = floor((length)/2); i >= 0 ; i--)
		heapify(A, length, i);
}

void Sorts::heapify(int A[], int heapsize, int root){
    int left = 2*root+1, 
		right = 2*root +2,
		largest;
	
	if ( (left < heapsize) && (A[left] > A[root]))
		largest = left;
	else 
		largest = root;
	
	if ( (right < heapsize) && (A[right] > A[largest]))
		largest = right;
		
	if (largest != root)
	{
		swap(A[root], A[largest]);
		heapify(A, heapsize, largest);
	}
}
//bubble sort
void Sorts::bubble(int a[], const int size){
    int temp;
    bool swap;
    
    do{
        swap = false;
        for(int i = 0; i < size; i++){
            if(a[i] > a[i + 1]){
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                swap = true;
            }
        }
    }while(swap);
}
//selection sort
void Sorts::selection(int a[], const int size){
    int minIndex;
    int minValue;
    
    for(int i = 0; i < size; i++){
        minIndex = i;
        minValue = a[i];
        for(int j = i + 1; j < size + 1; j++){
            if(a[j] < minValue){
                minValue = a[j];
                minIndex = j;
            }
        }
        a[minIndex] = a[i];
        a[i] = minValue;
    }
}
//insertion sort
void Sorts::insertion(int a[], const int size){
    int j;
    int temp;
    
    for(int i = 1; i < size; i++){
        j = i;
        while(j > 0 && a[j - 1] > a[j]){
            temp = a[j];
            a[j] = a[j - 1];
            a[j - 1] = temp;
            j--;
        }
    }
}
//get top p elements in an array
//returns pointer to array holding those tops
int *Sorts::topElements(int a[], int topElements){
    
    //create array to hold tops
    int *array = new int[topElements];
    
    //copy top p elements
    for(int i = 0; i < topElements; i++){
        array[i] = a[i];
    }
    
    return array; //return pointer to array
}
//show sort options
void Sorts::sortOptions(){
    cout << "Enter number corresponding to select a sort" << endl;
    cout << "1.) Quick Sort"<<endl;
    cout << "2.) Merge Sort"<<endl;
    cout << "3.) Heap Sort"<<endl;
    cout << "4.) Bubble Sort"<<endl;
    cout << "5.) Selection Sort"<<endl;
    cout << "6.) Insertion Sort"<<endl;
    cout<<"Type 7 or higher for none"<<endl;
}
//answer question on final
void Sorts::findings(){
    cout << "After analyzing the different sort function i have come to the \n"
            << "conclusion that the routines that can be configured to have the \n"
            << "shortest time would be merge sort and heap sort because across \n"
            << "their best and worst case the take O(n log(n)) time \n"
            << "to complete while the others worst time is O(n^2) time to complete \n"
            << "which was noticeable during testing these routines \n" 
            << "quick sort would be the next best option after merge and heap as \n"
            << "it has a best case of O(n log(n)) time but suffers from a worst case \n"
            << "of O(n^2) time, the rest are to slow for the 100000 elements" << endl;
}
#endif /* PROBLEM4_H */

