// определение класса Statistics
// подсчет статистических характеристик
#include "Statistics.h"
using namespace std;

// конструктор по умолчанию
Statistics::Statistics(){}
// деструктор по умолчанию
Statistics::~Statistics(){}

double Statistics::SumElements(vector<double> elements)
{
    double sum = 0.0;
    for_each(elements.begin(), elements.end(), [&](double elem)
    {
        sum += elem;
    });
    return sum;
}

double Statistics::MeanElements(vector<double> elements)
{
    double mean = 0.0;
    mean = this->SumElements(elements) / (double) elements.size();
    return mean;
}

double Statistics::GetExpectedValue(vector<double> elements)
{
    return 0.0;
}

double Statistics::GetDispersion(vector<double> elements)
{
    return 0.0;
}

double Statistics::GetMedian(vector<double> elements)
{
    double median = 0.0;
    int N = elements.size();
    if(N % 2 != 0) // для нечетного числа элементов
        median = elements.at(N / 2);
    else
    {
        median = (elements.at(N/2 - 1) + elements.at(N/2)) / 2.0;
    }

    return median;
}

vector<double> Statistics::SortVector(vector<double> elements)
{
    sort(elements.begin(), elements.end());
    return elements;
}