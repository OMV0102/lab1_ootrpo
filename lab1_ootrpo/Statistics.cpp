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

// ���������� ������� �������������� ��������� ������������������ (���. ��������)
double Statistics::GetMean(vector<double> elements)
{
    double mean = 0.0;
    mean = this->SumElements(elements) / (double) elements.size();
    return mean;
}

// ������� ��������� �������� ������������������
double Statistics::GetDispersion(vector<double> elements)
{
    double mean = this->GetMean(elements);
    double disp = 0.0;
    int N = elements.size();
    // ������� ���. �������� ��� sum(elem[i]^2)/N - mean^2
    for(int i = 0; i < N; i++)
    {
        disp += pow(elements[i] - mean, 2.0);
    }
    disp /= (double) N;

    return disp;
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
    if(2*k + 1 > elements.size()) throw "���������� ��������� ������� ����, ����� ��������� ��������� ������� ��� ��������� �������� ��������!";
    elements = this->SortVector(elements, true);
    // �������� k ��������� � ������ � �����
    for(int i = 0; i < k; i++)
    {
        elements.erase(elements.begin());
        elements.pop_back();
    }
    // ������� �������� �������� ��� ��������� ���������
    trMean = this->GetMean(elements);
    return trMean;
}

// ������� ���������������� �������� c ��������� %
double Statistics::GetWinsorizedMean(vector<double> elements, double percent)
{
    double trMean = 0.0;
    int N = elements.size();
    int k = (int) (N * percent);
    if(2*k > elements.size()) throw "���������� ��������� ������� ����, ����� ��������� ��������������� ������� ��� ��������� ��������!";
    elements = this->SortVector(elements, true);
    // ������ k ��������� � ������ � ����� �� k+1 (��� N-k-1)
    for(int i = 0; i < k; i++)
    {
        elements[i] = elements[k];
        elements[N-1-i] = elements[N-1-k];
    }
    // ������� �������� �������� ��� ��������� ���������
    trMean = this->GetMean(elements);
    return trMean;
}
