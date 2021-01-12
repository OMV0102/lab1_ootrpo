// реализация класса Statistics
// подсчет статистических характеристик
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

static struct intervalStruct
{
	double left; // нижняя граница интервала
	double right; // верхняя граница интервала
	int elemNumber = 0; // количество элементов последовательности в интервале
};

class Statistics
{
	public:
	Statistics(double v); // конструктор
	~Statistics(); // деструктор по умолчанию

	// поля класса
	private:
	static const int cofSize = 8; // размер таблицы коэффициентов
	static double cof[cofSize]; // таблица коэффициентов для GammaLn
	double v; // параметр формы;
	double betaValue; // параметр формы;

	// методы класса
	public:
	vector<double> SortVector(vector<double> elements, bool sortMode);
	double SumElements(std::vector<double> elements);
	double GetMean(vector<double> elements);
	double GetDispersion(vector<double> elements);
	double GetMedian(vector<double> elements);
	double GetTrimmedMean(vector<double> elements, double percent);
	double GetWinsorizedMean(vector<double> elements, double percent);
	vector<intervalStruct> DivideOnIntervals(vector<double> elements);
	bool CheckNonZeroInterval(vector<double> elements, int intervalNum, vector<intervalStruct> *intervals);
	bool CheckChiSquaredTest(vector<intervalStruct> intervals, int n);
	double f(double x); // вычисление значения функции плотности распределения Пирсона II типа
	double Probability(double a, double b, int stepCount); // вычисление вероятности (методом трапеций численного интегрирования)
	double Beta(double x, double y); // Вычисление бета - функции для x > 0, y > 0
	double Gamma(double x); // Вычисление гамма - функции для x > 0	
	
	private:
	double GammLn(double x); // Вычисление логарифма гамма - функции для x > 0

	
};