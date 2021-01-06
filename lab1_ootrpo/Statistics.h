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

	double SumElements(std::vector<double> elements);
	double SumElementsAbs(vector<double> elements);

	private:
};