// реализация класса Statistics
// подсчет статистических характеристик
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

class Statistics
{
	public:
	Statistics(); // конструктор по умолчанию
	~Statistics(); // деструктор по умолчанию

	public:
	vector<double> SortVector(vector<double> elements, bool sortMode);
	double SumElements(std::vector<double> elements);
	double GetMean(vector<double> elements);
	double GetDispersion(vector<double> elements);
	double GetMedian(vector<double> elements);
	double GetTrimmedMean(vector<double> elements, double percent);
	double GetWinsorizedMean(vector<double> elements, double percent);
	void DivideOnIntervals(vector<double> elements);

	private:
	double GammLn(double x); // Вычисление логарифма гамма - функции для x > 0
	double Gamma(double x); // Вычисление гамма - функции для x > 0
	static const int cofSize = 8; // размер таблицы коэффициентов
	static double cof[cofSize]; // таблица коэффициентов для GammaLn

	public:
	double Beta(double x, double y); // Вычисление бета - функции для x > 0, y > 0
	
};