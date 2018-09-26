#include <iostream>
#include <sstream>
#include <string>
# include <ctime>
#include <fstream>
#include <time.h>
#include <math.h>
#include <vector>


using namespace std;
int max(int a, int b);
int max(int a, int b, int c);
int Algorithm_1(int X[], int size);
int Algorithm_2(int X[], int size);
int MaxSum(int X[], int L, int U);
int Algorithm_4(int X[], int size);
void output(int X[]);
int* randomArray(int sequenceSize);


int max(int a, int b) 
{
    return a < b ? b : a;
}

int max(int a, int b, int c) 
{
    int firstMax = a < b ? b : a;
    return c < firstMax ? firstMax : c;
}

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

void output(int X[]) 
{
    cout << "algorithm-1: " << Algorithm_1(X, 10) << ";";
    cout << "algorithm-2: " << Algorithm_2(X, 10) << ";";
    cout << "algorithm-3: " << MaxSum(X, 0, 9) << ";";
    cout << "algorithm-4: " << Algorithm_4(X, 10) << ";";
}

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

int main() 
{
    int X[10], counter = 0;
    char charNum[10];
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
    output(X);

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
    while (sequenceSize <= 100)
    {
        int* A = randomArray(sequenceSize);

        clock_t timet1 = clock();
        for (int n = 0; n < 2500; n++)
        {
            Algorithm_1(A, sequenceSize);
        }      
        double elapsed_timet1 = double(clock() - timet1) / CLOCKS_PER_SEC;

        clock_t timet2 = clock();
        for (int n = 0; n < 2500; n++)
        {
            Algorithm_2(A, sequenceSize);
        }
        double elapsed_timet2 = double(clock() - timet2) / CLOCKS_PER_SEC;

        clock_t timet3 = clock();
        for (int n = 0; n < 2500; n++)
        {
            MaxSum(A, 0, sequenceSize - 1);
        }
        double elapsed_timet3 = double(clock() - timet3) / CLOCKS_PER_SEC;

        clock_t timet4 = clock();
        for (int n = 0; n < 2500; n++)
        {
            Algorithm_4(A, sequenceSize);
        }
        double elapsed_timet4 = double(clock() - timet4) / CLOCKS_PER_SEC;

        outFile << elapsed_timet1 * 100000 << ",";
        outFile << elapsed_timet2 * 100000 << ",";
        outFile << elapsed_timet3 * 100000 << ",";
        outFile << elapsed_timet4 * 100000 << ",";
       
        int t1 = ((2 * pow(sequenceSize, 3)) + (12 * pow(sequenceSize, 2)) + (22 * sequenceSize) + 24) / 10;
        int t2 = ((11 * pow(sequenceSize, 2)) + (17 * sequenceSize) + 8) / 10;
        int t3 = (((2 * sequenceSize) * log2(sequenceSize) + ((23 * sequenceSize) / 2) + 31) + 9) / 10;
        int t4 = ((19 * sequenceSize) + 5) / 10;

        outFile << t1 << ",";
        outFile << t2 << ",";
        outFile << t3 << ",";
        outFile << t4 << "\n";
        sequenceSize += 5;
    }
    outFile.close();
    return 0;
}
