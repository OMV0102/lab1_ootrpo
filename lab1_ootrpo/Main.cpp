// ���� ���� �������� ������� "main".����� ���������� � ������������� ���������� ���������.

#include <iostream>
#include "PRNG.h"
#include "Statistics.h"
using namespace std;

void main()
{
    PRNG prng;
    prng.SetV(0.5);
    vector<double> sequence;
    string errorMessage = "";
    int number = 10;
    Statistics stat;
    bool result = prng.GetSequence(number, &sequence, &errorMessage);
    setlocale(LC_ALL, "Russian");
    if(result == false)
        cout << errorMessage << endl;
    else
        for(int i = 0; i < number; i++)
        {
            cout << sequence[i] << endl;

        }
    
    double median = stat.GetMedian(sequence);
    cout << "\nmedian = " << median << endl;
    
    sequence = stat.SortVector(sequence, true);
    for(int i = 0; i < number; i++)
    {
        cout << sequence[i] << endl;

    }
    
}

