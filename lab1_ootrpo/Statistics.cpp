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

// Возвращает среднее арифметическое элементов последовательности (Мат. ожидание)
double Statistics::GetMean(vector<double> elements)
{
    double mean = 0.0;
    mean = this->SumElements(elements) / (double) elements.size();
    return mean;
}

// Подсчет дисперсии числовой последовательности
double Statistics::GetDispersion(vector<double> elements)
{
    double mean = this->GetMean(elements);
    double disp = 0.0;
    int N = elements.size();
    // подсчет мат. ожидания как sum(elem[i]^2)/N - mean^2
    for(int i = 0; i < N; i++)
    {
        disp += pow(elements[i] - mean, 2.0);
    }
    disp /= (double) N;

    return disp;
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
    if(2*k + 1 > elements.size()) throw "Количество элементом слишком мало, чтобы посчитать усеченное среднее для заданного процента усечения!";
    elements = this->SortVector(elements, true);
    // удаление k элементов в начале и конце
    for(int i = 0; i < k; i++)
    {
        elements.erase(elements.begin());
        elements.pop_back();
    }
    // подсчет обычного среднего без удаленных элементов
    trMean = this->GetMean(elements);
    return trMean;
}

// Подсчет винзорированного среднего c указанием %
double Statistics::GetWinsorizedMean(vector<double> elements, double percent)
{
    double trMean = 0.0;
    int N = elements.size();
    int k = (int) (N * percent);
    if(2*k > elements.size()) throw "Количество элементом слишком мало, чтобы посчитать винзорированное среднее для заданного процента!";
    elements = this->SortVector(elements, true);
    // замена k элементов в начале и конце на k+1 (или N-k-1)
    for(int i = 0; i < k; i++)
    {
        elements[i] = elements[k];
        elements[N-1-i] = elements[N-1-k];
    }
    // подсчет обычного среднего без удаленных элементов
    trMean = this->GetMean(elements);
    return trMean;
}

// Функция разбивает последовательность на интервалы для критерия хи^2
vector<intervalStruct> Statistics::DivideOnIntervals(vector<double> elements)
{
    vector<intervalStruct> intervals;
    int elemNum = elements.size(); // количество элементов в последовательности
    int intervalNum = 2; // количество интервалов

    // определение начального количества интервалов
    if(elemNum >= 40 && elemNum <= 100)
        intervalNum = 10;
    else if(elemNum >=100  && elemNum <= 500)
        intervalNum = 15;
    else if(elemNum >= 500 && elemNum <= 1000)
        intervalNum = 20;
    else if(elemNum >= 1000 && elemNum <= 10000)
        intervalNum = 25;
    else if(elemNum >= 1000)
        intervalNum = 30;

    while(true)
    {
        if(this->CheckNonZeroInterval(elements, intervalNum, &intervals) == true)
            break;
        else
        {
            intervalNum--;
        }
    }

    return intervals;

}

// Проверка. что в каждом интервале есть хотя бы одно попадание
// Если кол-во интервалов верно выбрано (return true), то в intervals буду границы интервалов
bool Statistics::CheckNonZeroInterval(vector<double> elements, int intervalNum, vector<intervalStruct> *intervals)
{
    double intervalSize = 0.0; // Размер одного интервала
    vector<intervalStruct> vectorTemp; // временный вектор для хранения интервалов
    intervalStruct temp;
    bool result = true; // результат разделения последовательности на интервалы
    int elemNumAll = elements.size(); // количество элементов в последовательности
    intervalSize = (elements[elemNumAll - 1] - elements[0]) / (double) intervalNum;
    elements = this->SortVector(elements, true); // сортируем элементы по возрастанию
    
    
    int i = 0;
    while(result == true && i < intervalNum)
    {
        temp.elemNumber = 0;
        temp.left = elements[0] + i * intervalSize;
        temp.right = elements[0] + (double)(i+1) * intervalSize;
        int j = 0;
        if(i == 0) { temp.elemNumber++; j++; } // первый элемент[0] в любом случае будет в первом интервале
        for(j; j < elemNumAll; j++)
        {
            if(temp.left < elements[j] && elements[j] <= temp.right)
                temp.elemNumber++;
        }
        vectorTemp.push_back(temp);
        if(temp.elemNumber < 1) result = false;
        i++;
    }
    if(result == true) *intervals = vectorTemp;

    return result;
}

// Логарифм гамма-функции
double Statistics::GammLn(double x)
{
    double y, ser, *co;
    int j;
    // вычисление последовательностей
    ser = cof[1];
    y = x;
    co = cof + 2;
    for(j = 2; j < cofSize; j++)
    {
        y += 1.;
        ser += (*co) / y;
        co++;
    }
    // и других частей функции
    y = x + 5.5;
    y -= (x + 0.5) * log(y);
    y = -y + log(cof[0] *ser / x);
    return y;
}

// Таблица коэффициентов для GammaLn
double Statistics::cof[cofSize] = {
    2.5066282746310005,
    1.0000000000190015,
    76.18009172947146,
    -86.50532032941677,
    24.01409824083091,
    -1.231739572450155,
    0.1208650973866179e-2,
    -0.5395239384953e-5};

// Гамма-функция
double Statistics::Gamma(double x)
{
    return(exp(GammLn(x)));
}

// Бета-функция
double Statistics::Beta(double x, double y)
{
    return(exp(GammLn(x) + GammLn(y) - GammLn(x + y)));
}
