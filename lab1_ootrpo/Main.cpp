// Этот файл содержит функцию "main".Здесь начинается и заканчивается выполнение программы.

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
    int number = 1000;
    double alpha = 0.05; // уровень значимости
    Statistics stat = Statistics(prng.GetV());
    bool result = prng.GetSequence(number, &sequence, &errorMessage);
    setlocale(LC_ALL, "Russian");
    if(result == false)
    {
        cout << errorMessage << endl;
        return;
    }
    //else
    //    for(int i = 0; i < number; i++)
    //    {
    //        cout << sequence[i] << endl;

    //    }
    
    cout << "\nmedian = " << stat.GetMedian(sequence) << endl;

    cout << "\nTrimmedMean = " << stat.GetTrimmedMean(sequence, alpha) << endl;

    cout << "\nWinsorizedMean = " << stat.GetWinsorizedMean(sequence, alpha) << endl;
    
    vector<intervalStruct> intervals = stat.DivideOnIntervals(sequence);
    bool res = stat.CheckChiSquaredTest(intervals, sequence.size(), alpha);
    cout << "\nChiSquared = " << res << endl;
}

