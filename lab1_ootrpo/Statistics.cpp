// ����������� ������ Statistics
// ������� �������������� �������������
#include "Statistics.h"
using namespace std;

// ����������� �� ���������
Statistics::Statistics(){}
// ���������� �� ���������
Statistics::~Statistics(){}

// ���������� ������������������
// ���� true - �� �����������; false - �� �������� 
vector<double> Statistics::SortVector(vector<double> elements, bool sortMode)
{
    if(sortMode == true)
        sort(elements.begin(), elements.end()); // ���������� �� �����������
    else
        sort(elements.begin(), elements.end(), greater<double>()); // ���������� �� ��������
    
    return elements;
}

// ���������� ����� ���������
double Statistics::SumElements(vector<double> elements)
{
    double sum = 0.0;
    for_each(elements.begin(), elements.end(), [&](double elem)
    {
        sum += elem;
    });
    return sum;
}

// ���������� ������� �������������� ��������� ������������������
double Statistics::MeanElements(vector<double> elements)
{
    double mean = 0.0;
    mean = this->SumElements(elements) / (double) elements.size();
    return mean;
}

// ������� ������� ������������������
double Statistics::GetMedian(vector<double> elements)
{
    double median = 0.0;
    int N = elements.size();
    if(N % 2 != 0) // ��� ��������� ����� ���������
        median = elements.at(N / 2); // ������� � ��������� ������������������
    else // ��� ������� ����� ���������
    {
        // ������� �������������� ���� ����������� ���������
        median = (elements.at(N/2 - 1) + elements.at(N/2)) / 2.0;
    }

    return median;
}

// ������� ���������� �������� c ��������� %
double Statistics::GetTrimmedMean(vector<double> elements, double percent)
{
    double trMean = 0.0;
    int k = (int)(elements.size() * percent);
    elements = this->SortVector(elements, true);
    // �������� k ��������� � ������ � �����
    for(int i = 0; i < k; i++)
    {
        elements.erase(elements.begin());
        elements.pop_back();
    }
    // ������� �������� �������� ��� ��������� ���������
    trMean = this->MeanElements(elements);
    return trMean;
}

//TODO ��������� (??????????)
double Statistics::GetDispersion(vector<double> elements)
{
    return 0.0;
}
