// ����������� ������ Statistics
// ������� �������������� �������������
#include "Statistics.h"
using namespace std;

// ����������� �� ���������
Statistics::Statistics(){}
// ���������� �� ���������
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

double Statistics::SumElementsAbs(vector<double> elements)
{
    double sum = 0.0;
    for_each(elements.begin(), elements.end(), [&](double elem)
    {
        sum += abs(elem);
    });
    return sum;
}