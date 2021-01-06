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
    int number = 20;
    bool result = prng.GetSequence(number, &sequence, &errorMessage);
    setlocale(LC_ALL, "Russian");
    if(result == false)
        cout << errorMessage << endl;
    else
        for(int i = 0; i < number; i++)
        {
            //cout << sequence[i] << endl;

        }
    double sum = 0.0;
    for_each(sequence.begin(), sequence.end(), [&](double elem)
    {
        sum += abs(elem);
    });
    sum /= (double)sequence.size();
    cout << "sum1 = " << sum << endl;
    sum = 0.0;
    for(int i = 0; i < sequence.size(); i++)
    {
        sum +=abs(sequence[i]);
    }
    sum /= (double) sequence.size();
    cout << "sum2 = " << sum << endl;
}

