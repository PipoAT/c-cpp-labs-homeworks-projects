//Names = "Andrew Pipo, Leo Nguyen, Sam Winkelmann, Thavishka Gamage"
//Emails = "pipoat@mail.uc.edu", "nguye2cy@mail.uc.edu", "winkelse@mail.uc.edu", "gamagetd@mail.uc.edu", 


#include <stdio.h>
#include <cstdio>
#include <ctime>
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
		swapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
				swapped = true;
			}
		}
		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
}

/* Function to print an array */

//BUBBLE_SORT_PERFORMANCE:
/*
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("n");
}
// Driver program to test above functions
int main()
{
	int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
	int n = sizeof(arr) / sizeof(arr[0]);
	bubbleSort(arr, n);
	printf("Sorted array: \n");
	printArray(arr, n);
	return 0;
} */


#include <stdio.h>
#include <math.h>

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
// A utility function to print an array of size n

//INSERTION SORT PERFORMANCE:
/*void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int main()
{
	int arr[] = { 12, 11, 13, 5, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);
	insertionSort(arr, n);
	printArray(arr, n);
	return 0;
}*/


#include<stdlib.h>
#include<stdio.h>
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	//create temp arrays
	int L[n1], R[n2];
	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;
		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}


//MERGE-SORT PERFORMANCE:
/*
void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	printf("Given array is \n");
	printArray(arr, arr_size);
	mergeSort(arr, 0, arr_size - 1);
	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	return 0;
}
*/
// Output:-
// Given array is 12 11 13 5 6 7 
// Sorted array is 5 6 7 11 12 13


#include <bits/stdc++.h>
using namespace std;

// A utility function to swap two elements

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i
        = (low
        - 1); // Index of smaller element and indicates
                // the right position of pivot found so far

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//Function to print an array
// QUICK SORT PERFORMANCE:
/*
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver Code
int main()
{
    int arr[] = { 10, 7, 8, 9, 1, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    cout << "Sorted array: \n";
    printArray(arr, n);
    return 0;
}
*/

#include <iostream>
using namespace std;
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int arr[], int N, int i)
{

    // Initialize largest as root
    int largest = i;

    // left = 2i + 1
    int l = 2*i + 1;

    // right = 2i + 2
    int r = 2*i + 2;

    // If left child is larger than root
    if (l < N && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest
    // so far
    if (r < N && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int N)
{

    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);

    // One by one extract an element
    // from heap
    for (int i = N - 1; i > 0; i--) {

        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
/* UTILITY FUNCTIONS */
/* Function to print an array */

//HEAP SORT PERFORMANCE: 
/*
void printArray(int arr[], int N)
{
    for (int i = 0; i < N; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// Driver's code
int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int N = sizeof(arr) / sizeof(arr[0]);

    // Function call
    heapSort(arr, N);

    cout << "Sorted array is \n";
    printArray(arr, N);
}
*/
// C++ Program for counting sort
#include <bits/stdc++.h>
#include <string.h>
using namespace std;
#define RANGE 255

// The main function that sort
// the given string arr[] in
// alphabetical order

//COUNTING SORT
/*
void countSort(char arr[])
{
    // The output character array
    // that will have sorted arr
    char output[strlen(arr)];

    // Create a count array to store count of individual
    // characters and initialize count array as 0
    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));

    // Store count of each character
    for (i = 0; arr[i]; ++i)
        ++count[arr[i]];

    // Change count[i] so that count[i] now contains actual
    // position of this character in output array
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];

    // Build the output character array
    for (i = 0; arr[i]; ++i) {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    /*
    For Stable algorithm
    for (i = sizeof(arr)-1; i>=0; --i)
    {
        output[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }

    For Logic : See implementation
    */

    // Copy the output array to arr, so that arr now
    // contains sorted characters

/*
		for (i = 0; arr[i]; ++i)
        arr[i] = output[i];
}
// Driver code
int main()
{
    char arr[] = "test";

    // Function call
    countSort(arr);

    cout << "Sorted character array is " << arr;
    return 0;
}
*/


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int RadixGetLength(int value) {
   if (value == 0) {
      return 1;
   }
      
   int digits = 0;
   while (value != 0) {
      digits++;
      value /= 10;
   }
   return digits;
}

// Returns the maximum length, in number of digits, out of all array elements
int RadixGetMaxLength(int* numbers, int numbersSize) {
   int maxDigits = 0;
   for (int i = 0; i < numbersSize; i++) {
      int digitCount = RadixGetLength(numbers[i]);
      if (digitCount > maxDigits) {
         maxDigits = digitCount;
      }
   }
   return maxDigits;
}
//RADIX SORT PERFORMANCE:
/*
void RadixSort(int* numbers, int numbersSize) {
   vector<vector<int>*> buckets;
   for (int i = 0; i < 10; i++) {
      vector<int>* bucket = new vector<int>();
      buckets.push_back(bucket);
   }
      
   int copyBackIndex = 0;
      
   // Find the max length, in number of digits
   int maxDigits = RadixGetMaxLength(numbers, numbersSize);
      
   int pow10 = 1;
   for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
      // Put numbers into buckets
      for (int i = 0; i < numbersSize; i++) {
         int num = numbers[i];
         int bucketIndex = (abs(num) / pow10) % 10;
         buckets[bucketIndex]->push_back(num);
      }
         
      // Copy buckets back into numbers array
      copyBackIndex = 0;
      for (int i = 0; i < 10; i++) {
         vector<int>& bucket = *buckets[i];
         for (int j = 0; j < bucket.size(); j++) {
            numbers[copyBackIndex] = bucket[j];
            copyBackIndex++;
         }
         bucket.clear();
      }
      
      pow10 *= 10;
   }
      
   vector<int> negatives;
   vector<int> nonNegatives;
   for (int i = 0; i < numbersSize; i++) {
      int num = numbers[i];
      if (num < 0) {
         negatives.push_back(num);
      }
      else {
         nonNegatives.push_back(num);
      }
   }
      
   // Copy sorted content to array - negatives in reverse, then non-negatives
   copyBackIndex = 0;
   for (int i = negatives.size() - 1; i >= 0; i--) {
      numbers[copyBackIndex] = negatives[i];
      copyBackIndex++;
   }
   for (int i = 0; i < nonNegatives.size(); i++) {
      numbers[copyBackIndex] = nonNegatives[i];
      copyBackIndex++;
   }
   
   // Free each dynamically allocated bucket
   for (int i = 0; i < 10; i++) {
      delete buckets[i];
   }
}

string ArrayToString(int* array, int arraySize) {
   // Special case for empty array
   if (0 == arraySize) {
      return string("[]");
   }
   
   // Start the string with the opening '[' and element 0
   string result = "[" + to_string(array[0]);
   
   // For each remaining element, append comma, space, and element
   for (int i = 1; i < arraySize; i++) {
      result += ", ";
      result += to_string(array[i]);
   }
   
   // Add closing ']' and return result
   result += "]";
   return result;
}
    
int main() {
   // Create an array of numbers to sort
   int numbers[] = { -9, 47, 81, 101, -5, 38, -99, 96, 51, -999, -11, 64 };
   int numbersSize = sizeof(numbers) / sizeof(numbers[0]);
      
   // Display the contents of the array
   cout << "UNSORTED: " << ArrayToString(numbers, numbersSize) << endl;
      
   // Call the RadixSort function
   RadixSort(numbers, numbersSize);
      
   // Display the sorted contents of the array
   cout << "SORTED:   " << ArrayToString(numbers, numbersSize) << endl;
}
*/