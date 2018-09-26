/*
* Program: Algorithm Implementations
* Author: Christopher Tillery
* 07/07/2018
* -----------------------------------------------------
* Implements five algorithms which calculate the maxSum of 
* all the numbers in a file.
*/

// Source file inclusion
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <fstream>
#include <time.h>
#include <math.h>

using namespace std; // Declare namespace

// Forward declaration of functions
int max(int a, int b);
int max(int a, int b, int c);
int Algorithm_1(int X[], int size);
int Algorithm_2(int X[], int size);
int MaxSum(int X[], int L, int U);
int Algorithm_4(int X[], int size);
void output(int X[]);
int* randomArray(int sequenceSize);

/*
* Function: main
* --------------------
*  Reads from an input file an array, calculates the sum of the array with
*  four algorithms, runs the algorithms on 19 different sized algorithms 2500 
*  times each and records the elapsed time, and prints the elapsed and estimated 
*  time taken
*/
int main() 
{
    // Storage variables for input data
    int X[10], counter = 0;
    char charNum[10];

    // Read input data and store inside array X
    // The only code from an external source is in lines 46 - 61. The code comes from a user on the cplusplus.com forums.
    // Source: http://www.cplusplus.com/forum/general/17771/ User: sndpgandra
    ifstream inFile;
    inFile.open("phw_input.txt");
    if (inFile.is_open())
    {
        while (inFile.good())
        {
            inFile.getline(charNum, 256, ',');
            X[counter] = atoi(charNum);
            counter++;
        }
        inFile.close();
    }
    else
    {
        cerr << "Error: File cannot be opened. \n";
    }
    // End imported code

    output(X); // Output the return values for all four algorithms with input array X

    // Open output file and initialize loop variable
    int sequenceSize = 10;
    ofstream outFile("ChristopherTillery_phw_output.txt");
    if (outFile.is_open())
    {
        outFile << "algorithm-1,algorithm-2,algorithm-3,algorithm-4,T1(n),T2(n),T3(n), T4(n)\n";
    }
    else 
    {
        cout << "Unable to open file";
    }

    // Loop 19 times executing each algorithm 2500 times for all 19 values of sequenceSize
    while (sequenceSize <= 100)
    {
        int* A = randomArray(sequenceSize); // Create a random array to use as input

        // Record time for algorithm 1
        clock_t timet1 = clock();
        for (int n = 0; n < 2500; n++)
        {
            Algorithm_1(A, sequenceSize);
        }      
        double elapsed_timet1 = double(clock() - timet1) / CLOCKS_PER_SEC;

        // Record time for algorithm 2
        clock_t timet2 = clock();
        for (int n = 0; n < 2500; n++)
        {
            Algorithm_2(A, sequenceSize);
        }
        double elapsed_timet2 = double(clock() - timet2) / CLOCKS_PER_SEC;

        // Record time for algorithm 3
        clock_t timet3 = clock();
        for (int n = 0; n < 2500; n++)
        {
            MaxSum(A, 0, sequenceSize - 1);
        }
        double elapsed_timet3 = double(clock() - timet3) / CLOCKS_PER_SEC;

        // Record time for algorithm 3
        clock_t timet4 = clock();
        for (int n = 0; n < 2500; n++)
        {
            Algorithm_4(A, sequenceSize);
        }
        double elapsed_timet4 = double(clock() - timet4) / CLOCKS_PER_SEC;

        // Output elapsed times
        outFile << elapsed_timet1 * 100000 << ",";
        outFile << elapsed_timet2 * 100000 << ",";
        outFile << elapsed_timet3 * 100000 << ",";
        outFile << elapsed_timet4 * 100000 << ",";
       
        // Output estimated times
        int t1 = (int)((2 * pow(sequenceSize, 3)) + (12 * pow(sequenceSize, 2)) + (22 * sequenceSize) + 24) / 10;
        int t2 = (int)((11 * pow(sequenceSize, 2)) + (17 * sequenceSize) + 8) / 10;
        int t3 = (int)((2 * sequenceSize * log2(sequenceSize) + ((23 * sequenceSize) / 2) + 31) + 9) / 10;
        int t4 = (int)((19 * sequenceSize) + 5) / 10;

        // Output formatting
        outFile << t1 << ",";
        outFile << t2 << ",";
        outFile << t3 << ",";
        outFile << t4 << "\n";

        sequenceSize += 5; // Update loop variable
    }
    outFile.close();
    return 0;
}

/*
* Function: max(a, b)
* --------------------
*  Finds the larger number of two numbers.
*
*  a: integer one
*  b: integer two
*
*  returns: the larger of a and b
*/
int max(int a, int b) 
{
    return a < b ? b : a;
}

/*
* Function:  max(a, b, c)
* --------------------
*  Finds the largest number of three numbers.
*
*  a: integer one
*  b: integer two
*  c: integer three
*
*  returns: the largest of a, b, and c
*/
int max(int a, int b, int c) 
{
    int firstMax = a < b ? b : a;
    return c < firstMax ? firstMax : c;
}

/*
* Function:  Algorithm_1
* --------------------
* Calculate the maxSum of all the numbers in a file.
*
*  X[]: an array of integers
*  size: the size of X[]
*
*  Complexity: O(n^3)
*  returns: the sum of all integers in X[]
*/
int Algorithm_1(int X[], int size) 
{
    int maxSoFar = 0;
    int Q = size - 1;
    int P = 0;
    for (int L = P; L <= Q; L++) 
    {
        for (int U = L; U <= Q; U++) 
        {
            int sum = 0;
            for (int I = L; I <= U; I++)   
            {
                sum = sum + X[I];          
            }
            maxSoFar = max(maxSoFar, sum);
        }
    }
    return maxSoFar;
}

/*
* Function:  Algorithm_2
* --------------------
*  Calculate the maxSum of all the numbers in a file.
*
*  X[]: an array of integers
*  size: the size of X[]
*
*  Complexity: O(n^2)
*  returns: the sum of all integers in X[]
*/
int Algorithm_2(int X[], int size) 
{
    int maxSoFar = 0;
    int Q = size - 1;
    int P = 0;
    for (int L = P; L <= Q; L++) 
    {
        int sum = 0;
        for (int U = L; U <= Q; U++)
        {
            sum = sum + X[U];
            maxSoFar = max(maxSoFar, sum);
        }
    }
   return maxSoFar;
}

/*
* Function:  MaxSum
* --------------------
*  Calculate the maxSum of all the numbers in a file.
*
*  X[]: an array of integers
*  size: the size of X[]
*
*  Complexity: O(nlogn)
*  returns: the sum of all integers in X[]
*/
int MaxSum(int X[], int L, int U) 
{
    if (L > U) 
    {
        return 0;
    }
    if (L == U)
    {
        return max(0, X[L]);
    }
    int M = (L + U) / 2;
    int sum = 0;
    int maxToLeft = 0;
    for (int I = M; I >= L; I--)
    {
        sum = sum + X[I];
        maxToLeft = max(maxToLeft, sum);
    }
    sum = 0;
    int maxToRight = 0;
    for (int I = M + 1; I <= U; I++)
    {
        sum = sum + X[I];
        maxToRight = max(maxToRight, sum);
    }
    int maxCrossing = maxToLeft + maxToRight;
    int maxInA = MaxSum(X, L, M);
    int maxInB = MaxSum(X, M + 1, U);
    return max(maxCrossing, maxInA, maxInB);
}

/*
* Function:  Algorithm_4
* --------------------
*  Calculate the maxSum of all the numbers in a file.
*
*  X[]: an array of integers
*  size: the size of X[]
*
*  Complexity: O(n)
*  returns: the sum of all integers in X[]
*/
int Algorithm_4(int X[], int size)
{
    int maxSoFar = 0;
    int maxEndingHere = 0;
    int P = 0;
    int Q = size - 1;
    for (int I = P; I <= Q; I++)
    {
        maxEndingHere = max(0, maxEndingHere + X[I]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

/*
* Function:  output
* --------------------
*  Outputs the return from all four summing algorithms
*
*  X[]: an array of integers
*
*/
void output(int X[]) 
{
    cout << "algorithm-1: " << Algorithm_1(X, 10) << ";";
    cout << "algorithm-2: " << Algorithm_2(X, 10) << ";";
    cout << "algorithm-3: " << MaxSum(X, 0, 9) << ";";
    cout << "algorithm-4: " << Algorithm_4(X, 10) << ";";
}

/*
* Function:  randomArray
* --------------------
*  Generates a random array with positive, negative, and zeros
*
*  sequenceSize: the size of the new array
*
*  returns: the new random array
*/
int* randomArray(int sequenceSize) 
{
    int sign = 0;
    int* A = new int[sequenceSize];
    for (int i = 0; i < sequenceSize; i++)
    {
        sign = rand();
        if ((sign % 2) + 1 == 2)
        {
            A[i] = -rand();
        }
        else
        {
            A[i] = rand();
        }
    }
    return A;
}
