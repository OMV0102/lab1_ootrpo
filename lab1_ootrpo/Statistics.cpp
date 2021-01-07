// определение класса Statistics
// подсчет статистических характеристик
#include "Statistics.h"
using namespace std;

// конструктор по умолчанию
Statistics::Statistics(){}
// деструктор по умолчанию
Statistics::~Statistics(){}

// Сортировка последовательности
// флаг true - по возрастанию; false - по убыванию 
vector<double> Statistics::SortVector(vector<double> elements, bool sortMode)
{
    if(sortMode == true)
        sort(elements.begin(), elements.end()); // сортировка по возрастанию
    else
        sort(elements.begin(), elements.end(), greater<double>()); // сортировка по убыванию
    
    return elements;
}

// Возвращает сумму элементов
double Statistics::SumElements(vector<double> elements)
{
    double sum = 0.0;
    for_each(elements.begin(), elements.end(), [&](double elem)
    {
        sum += elem;
    });
    return sum;
}

// Возвращает среднее арифметическое элементов последовательности
double Statistics::MeanElements(vector<double> elements)
{
    double mean = 0.0;
    mean = this->SumElements(elements) / (double) elements.size();
    return mean;
}

// Подсчет медианы последовательности
double Statistics::GetMedian(vector<double> elements)
{
    double median = 0.0;
    int N = elements.size();
    if(N % 2 != 0) // для нечетного числа элементов
        median = elements.at(N / 2); // элемент в серединеф последовательсноти
    else // для четного числа элементов
    {
        // среднее арифметическое двух центральных элементов
        median = (elements.at(N/2 - 1) + elements.at(N/2)) / 2.0;
    }

    return median;
}

// Подсчет усеченного среднего c указанием %
double Statistics::GetTrimmedMean(vector<double> elements, double percent)
{
    double trMean = 0.0;
    int k = (int)(elements.size() * percent);
    elements = this->SortVector(elements, true);
    // удаление k элементов в начале и конце
    for(int i = 0; i < k; i++)
    {
        elements.erase(elements.begin());
        elements.pop_back();
    }
    // подсчет обычного среднего без удаленных элементов
    trMean = this->MeanElements(elements);
    return trMean;
}

//TODO дисперсия (??????????)
double Statistics::GetDispersion(vector<double> elements)
{
    return 0.0;
}
