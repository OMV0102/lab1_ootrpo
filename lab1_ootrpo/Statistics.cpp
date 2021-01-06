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

}

double Statistics::GetDispersion(vector<double> elements)
{

}

double Statistics::GetMedian(vector<double> elements)
{

}