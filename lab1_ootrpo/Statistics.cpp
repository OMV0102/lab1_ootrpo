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

// ������� ��������� ������������������ �� ��������� ��� �������� ��^2
void Statistics::DivideOnIntervals(vector<double> elements)
{
    vector<pair<double, double>> intervals;
    intervals.push_back(make_pair(1.5, 1.6));
    make_pair(1.5, 1.6);
    int elemSize = elements.size(); // ������ ������������������
    int N = 1; // ���������� ����������

    // ����������� ���������� ������� ������ ���������
    // ...
}

// �������� �����-�������
double Statistics::GammLn(double x)
{
    double y, ser, *co;
    int j;
    // ���������� �������������������
    ser = cof[1];
    y = x;
    co = cof + 2;
    for(j = 2; j < cofSize; j++)
    {
        y += 1.;
        ser += (*co) / y;
        co++;
    }
    // � ������ ������ �������
    y = x + 5.5;
    y -= (x + 0.5) * log(y);
    y = -y + log(cof[0] *ser / x);
    return y;
}

// ������� ������������� ��� GammaLn
double Statistics::cof[cofSize] = {
    2.5066282746310005,
    1.0000000000190015,
    76.18009172947146,
    -86.50532032941677,
    24.01409824083091,
    -1.231739572450155,
    0.1208650973866179e-2,
    -0.5395239384953e-5};

// �����-�������
double Statistics::Gamma(double x)
{
    return(exp(GammLn(x)));
}

// ����-�������
double Statistics::Beta(double x, double y)
{
    return(exp(GammLn(x) + GammLn(y) - GammLn(x + y)));
}
