// определение класса Statistics
// подсчет статистических характеристик
#include "Statistics.h"
using namespace std;

// конструктор по умолчанию
Statistics::Statistics(){}
// деструктор по умолчанию
Statistics::~Statistics(){}

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

//TODO мат ожидание (??????????)
double Statistics::GetExpectedValue(vector<double> elements)
{
    return 0.0;
}

//TODO дисперсия (??????????)
double Statistics::GetDispersion(vector<double> elements)
{
    return 0.0;
}

// Подсчет медианы последовательности
double Statistics::GetMedian(vector<double> elements)
{
    double median = 0.0;
    int N = elements.size();
    if(N % 2 != 0) // для нечетного числа элементов
        median = elements.at(N / 2); // элемент в середине последовательсноти
    else // для четного числа элементов
    {
        // среднее арифметическое двух центральных элементов
        median = (elements.at(N/2 - 1) + elements.at(N/2)) / 2.0;
    }

    return median;
}

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
