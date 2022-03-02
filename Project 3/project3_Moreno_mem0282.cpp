/* FILE NAME: project3_Moreno_mem0282.cpp
 * Name: Melvin Moreno
 * Auburn UserID: mem0282
 * I got the Merge-sort algorithm for C++ on geeksforgeeks.com
 * Found resources on how inStream.good() works on stack overflow.
 * Compile: g++ project3_Moreno_mem0282.cpp -o Project3.out
 * Run: ./Project3.out
 */

#include <fstream>
#include <iostream>
using namespace std;
//Only one global variable as per instructions.
const int MAX_SIZE = 100;

/* Input: (1) Array storing data retrieved from the file (i.e., inStream)
 *        (2) input file stream object
 * Output: Size of array. Note: you need to use this parameter to control the array size.
 */
int readfile (int inputArray[], ifstream& inStream) {
    int index = 0;

    inStream >> inputArray[index];
    while (!inStream.eof()) {
        index++;
        inStream >> inputArray[index];
    }
    return index;
    //If reading file failed return error message.
    if (inStream.fail()) {
        cout << "Could not read input file. Please check that you entered it correctly.";
        return -1;
    }
}

/*
 * Writes the output file with sorted array.
 */
void writefile(int outputArray[], int outputArray_size, string file) {
    ofstream outStream;
    outStream.open((char*)file.c_str());
    if (outStream.fail()) {
        cout << "Could not write to file";
    }
    else {
        for (int i = 0; i < outputArray_size; i++) {
            outStream << outputArray[i] << endl;
        }
    }
    outStream.close();
}

/* 
 * Merge-sort algorithm in C++
 */
void merge(int array[], int const left, int const mid, int const right) {
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    //Create temp arrays
    int *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
    
    //Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
    int indexOfSubArrayOne = 0, // Initial Index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left...right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    //Copy the remaining elements of left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayTwo];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    //Copy the remaining elements of right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

/* Merge the sorted arrays that were split in merge.
 * begin is for left index and end is right index
 * of the sub-array of arr to be sorted
 */
void mergeSort(int array[], int const begin, int const end) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

/*
 * Combines the arrays from both input files.
 */
int combineAndSort(int iArray1[], int iArray1_size, int iArray2[], int iArray2_size, int outputArray[]) {
    int outputArray_size = iArray1_size + iArray2_size;
    
    for (int i = 0; i < iArray1_size; i++) {
        outputArray[i] = iArray1[i];
    }
    for (int i = 0; i < iArray2_size; i++) {
        outputArray[i+iArray1_size] = iArray2[i];
    }
    mergeSort(outputArray, 0, outputArray_size);
    return outputArray_size;
}
/*
 * Merge the numbers in two specified files and write all the numbers
 * to a specified third file sorted in ascended order.
 * 
 * Return: 1 Program completed successfully. (int)
 */
int main() {
    ifstream inStream;

    int iArray1[MAX_SIZE];
    int iArray1_size;
    int iArray2[MAX_SIZE];
    int iArray2_size;
    int outputArray[MAX_SIZE];
    string fileName1;
    string fileName2;

    cout << "*** Welcome to Melvin's sorting program ***\n";
    bool fileCheck = false;
    while (!fileCheck) {
        cout << "Enter the first input file name: ";
        cin >> fileName1;
        inStream.open((char*)fileName1.c_str());
        fileCheck = inStream.good();

        if (!fileCheck) {
            cout << "Could not find input file. Please try again.";
            cout << endl;
    }
    }

    iArray1_size = readfile(iArray1, inStream);
    inStream.close();

        cout << "The list of " << iArray1_size << " numbers in file " << fileName1 << " is:\n";
        for (int i = 0; i < iArray1_size; i++) {
            cout << iArray1[i] << endl;
        }
        cout << endl;
    

    //Get second file
    bool fileCheck2 = false;
    while (!fileCheck2) {
    cout << "Enter the second input file name: ";
    cin >> fileName2;
    inStream.open((char*)fileName2.c_str());
    fileCheck2 = inStream.good();

    if (!fileCheck2) {
        cout << "Could not find input file. Please try again.";
        cout << endl;
    }
    }
    iArray2_size = readfile(iArray2, inStream);
    inStream.close();
        cout << "The list of " << iArray2_size << " numbers in file " << fileName2 << " is: \n";
        for (int i = 0; i < iArray2_size; i++) {
            cout << iArray2[i] << endl;
        }
        cout << endl;
    


    int outputArray_size = combineAndSort(iArray1, iArray1_size, iArray2, iArray2_size, outputArray);

    cout << "The sorted list of " << outputArray_size << " numbers is: ";
    for (int i = 0; i < outputArray_size; i++) {
        cout << outputArray[i] << " ";
    }
    cout << endl;

    //Write output file & enter string
    string outputFileName;
    cout << "Enter the output file name: ";
    cin >> outputFileName;
    writefile(outputArray, outputArray_size, outputFileName);
    cout << "*** Please check the new file - " << outputFileName << " ***\n";
    cout << "*** Goodbye. ***" << endl;
    return 0;
}
